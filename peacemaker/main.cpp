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

auto Logger = pm::Logger::Instance();

class TestCapture : public pm::Capture
{
public:
   TestCapture(const char* device) : pm::Capture(device)
   {
   }
   
   virtual void Callback(const struct pcap_pkthdr *header, const unsigned char *data)
   {
      pm::Capture::Callback(header, data);
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
