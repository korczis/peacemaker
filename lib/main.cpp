//
//  main.cpp
//  peacemaker
//
// The MIT License (MIT)
//
// Copyright (c) 2014 Tomas Korcak <korczis@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

// core c++ includes
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "Application/Application.h"
#include "Engine/Capture.h"
#include "Engine/Device.h"
#include "Engine/Engine.h"
#include "Logger/Logger.h"
#include "Packets/Packets.h"

// boost includes
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>

// pcap includes
#include <pcap.h>

auto Logger = pm::Logger::Instance();

class TestCapture : public pm::Capture
{
public:
   TestCapture(const char* device) : pm::Capture(device)
   {
   }
   
   virtual void Callback(const struct pcap_pkthdr *header, const unsigned char *data)
   {
      /* cast to generic packet */
      auto packet = (pm::Packet*)(data);
      
      /* get the ethernet header*/
      auto eth = packet->GetData<pm::PacketEthernet>();
      
      /* get the ip header */
      auto ip = eth->GetData<pm::PacketIp>();
      
      /* get the upd header */
      auto udp = ip->GetData<pm::PacketUdp>();
      
      /* print ip addresses and udp ports */
      char buffer[1024];
      snprintf(buffer, sizeof(buffer), "%s:%d -> %s:%d",
      	ip->Src().ToString().c_str(),
			udp->Sport(),
         ip->Dest().ToString().c_str(),
			udp->Dport()
		);
      Logger.Info(buffer);
      
      auto dns = udp->GetData<pm::PacketDns>();
      
      snprintf(buffer, sizeof(buffer), "Questions: %d", ntohs(dns->Qcount));
      Logger.Info(buffer);
      
      auto answers_count = ntohs(dns->Ancount);
      snprintf(buffer, sizeof(buffer), "Answers: %d", answers_count);
      Logger.Info(buffer);
      
      auto request = dns->GetRequest();
      snprintf(buffer, sizeof(buffer), "Q: %s, Type: %d, Class: %d", request->GetName().c_str(), request->GetType(), request->GetClass());
      Logger.Info(buffer);
      
      if(answers_count)
      {
         auto response_raw = ((unsigned char*)dns->GetResponse());
         int response_offset = 0;
         for(auto i = 0; i < 1 /* answers_count */; i++)
         {
            auto response = (pm::PacketDns::Response*)(response_raw + response_offset);
            auto type = ((const unsigned char*)response)[0];
            auto offset = ((const unsigned char*)response)[1];
            auto response_request = ((pm::PacketDns::Request*)(((unsigned char*)dns)+offset));
            auto name = response_request->GetName().c_str();
            
            snprintf(buffer, sizeof(buffer), "A: %s, Type: %02x, Offset: %02x, TTL: %d", name, type, offset, response->GetTtl());
            Logger.Info(buffer);
            
            response_offset += sizeof(pm::PacketDns::Response) + response->GetLength();
         }
      }
   }
};

int test(int argc, const char** argv)
{
   Logger.Log("Creating Engine");
   auto engine = new pm::Engine();
   
   auto device_name = argc > 2 ? argv[2] : "en0";
   
   Logger.Log("Getting device");
   auto device = engine->GetDevice(device_name);
   
   Logger.Log("Creating Capture");
   auto capture = device->CreateCapture<TestCapture>();
   
   Logger.Log("Setting filter");
   capture->SetFilter("udp port 53"); // udp port 53
   Logger.Log("Adding capture to engine");
   engine->AddCapture(capture);
   
   Logger.Log("Running Engine::Loop()");
   engine->Loop();
   
   Logger.Log("Removing capture from engine");
   engine->RemoveCapture(capture);
   
   Logger.Log("Deleting engine");
   delete engine;
   engine = NULL;
   
   return 0;
}

int main(const int argc, const char *argv[])
{
   if(argc >= 2 && strcmp(argv[1], "-t") == 0)
   {
   	return test(argc, argv);
   }
   
   // Create peacemaker application
	auto app = new pm::Application(argc, argv);
   
   auto res = app->Run();
   
   // Delete application
   delete app;
   app = 0;
   
   return res;
}
