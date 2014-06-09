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
   
   /* 4 bytes IP address */
   typedef struct ip_address {
      u_char byte1;
      u_char byte2;
      u_char byte3;
      u_char byte4;
   } ip_address;
   
   /* IPv4 header */
   typedef struct ip_header {
      u_char  ver_ihl;        // Version (4 bits) + Internet header length (4 bits)
      u_char  tos;            // Type of service
      u_short tlen;           // Total length
      u_short identification; // Identification
      u_short flags_fo;       // Flags (3 bits) + Fragment offset (13 bits)
      u_char  ttl;            // Time to live
      u_char  proto;          // Protocol
      u_short crc;            // Header checksum
      ip_address  saddr;      // Source address
      ip_address  daddr;      // Destination address
      u_int   op_pad;         // Option + Padding
   } ip_header;
   
   /* UDP header*/
   typedef struct udp_header {
      u_short sport;          // Source port
      u_short dport;          // Destination port
      u_short len;            // Datagram length
      u_short crc;            // Checksum
   } udp_header;

   
   virtual void Callback(const struct pcap_pkthdr *header, const unsigned char *data)
   {
      // pm::Capture::Callback(header, data);
      
      struct tm *ltime;
      char timestr[16];
      ip_header *ih = NULL;
      udp_header *uh = NULL;
      u_int ip_len;
      u_short sport,dport;
      time_t local_tv_sec;
      
      /* convert the timestamp to readable format */
      local_tv_sec = header->ts.tv_sec;
      ltime=localtime(&local_tv_sec);
      strftime( timestr, sizeof timestr, "%H:%M:%S", ltime);
      
      /* print timestamp and length of the packet */
      printf("%s.%.6d len:%d ", timestr, header->ts.tv_usec, header->len);
      
      /* retireve the position of the ip header */
      ih = (ip_header *) (data + 14); //length of ethernet header
      
      /* retireve the position of the udp header */
      ip_len = (ih->ver_ihl & 0xf) * 4;
      uh = (udp_header *) ((u_char*)ih + ip_len);
      
      /* convert from network byte order to host byte order */
      sport = ntohs(uh->sport);
      dport = ntohs(uh->dport);
      
      /* print ip addresses and udp ports */
      printf("%d.%d.%d.%d:%d -> %d.%d.%d.%d:%d\n",
			ih->saddr.byte1,
			ih->saddr.byte2,
			ih->saddr.byte3,
			ih->saddr.byte4,
			sport,
			ih->daddr.byte1,
			ih->daddr.byte2,
			ih->daddr.byte3,
			ih->daddr.byte4,
			dport
		);
   }
};

int test()
{
   Logger.Log("Creating Engine");
   auto engine = new pm::Engine();
   
   Logger.Log("Getting device");
   auto device = engine->GetDevice("en0");
   
   Logger.Log("Creating Capture");
   auto capture = device->CreateCapture<TestCapture>();
   
   Logger.Log("Setting filter");
   capture->SetFilter("");
   
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
   if(argc == 2 && strcmp(argv[1], "-t") == 0)
   {
   	return test();
   }
   
   // Create peacemaker application
	auto app = new pm::Application(argc, argv);
   
   auto res = app->Run();
   
   // Delete application
   delete app;
   app = 0;
   
   return res;
}
