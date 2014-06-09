//
//  main.cpp
//  peacemaker
//
//  Created by Tomas Korcak on 6/8/14.
//  Copyright (c) 2014 Tomas Korcak. All rights reserved.
//

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

int test()
{
   Logger.Log("Creating Engine");
   auto engine = new pm::Engine();
   
   Logger.Log("Getting device");
   auto device = engine->GetDevice("en0");
   
   Logger.Log("Creating Capture");
   auto capture = device->CreateCapture();
   
   Logger.Log("Setting filter");
   capture->SetFilter("");
   
   while(true)
   {
   	auto count = capture->Process();
      if(count < 1)
      {
         boost::this_thread::sleep(boost::posix_time::milliseconds(10));
      }
      else
      {
         // std::cout << count << std::endl;
      }
   }
   
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
