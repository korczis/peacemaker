//
//  Application.cpp
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

#include "Application.h"

// engine includes
#include "../Engine/Device.h"
#include "../Engine/Engine.h"

#include "../Logger/Logger.h"

// core c++ includes
#include <cstdlib>
#include <iostream>

// boost
#include <boost/program_options.hpp>

namespace po = boost::program_options;

using namespace pm;

Application::Application(const int& argc, const char** argv) : mArgc(argc), mArgv(argv), mEngine(new Engine())
{
   
}

Application::~Application()
{
   // Delete engine
   delete mEngine;
   mEngine = 0;
}

int Application::Run()
{
   // Declare the supported options.
   po::options_description desc("Allowed options");
   desc.add_options()
   	("help,h", "Show usage (this screen)")
   	("list,l", "List available devices")
   	("kill", "Kill all TCP connections")
   	("sniff", po::value<std::string>(), "Sniff in network traffic")
   ;
   
   po::variables_map vm;
   
   try
   {
      po::store(po::parse_command_line(mArgc, mArgv, desc), vm);
      po::notify(vm);
   }
   catch(po::error& e)
   {
      std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
      std::cerr << desc << std::endl;
      
      return EXIT_FAILURE;
   }
   
   if (vm.count("help") || mArgc < 2) {
      std::cout << desc << "\n";
      return EXIT_FAILURE;
   }

   if(vm.count("kill"))
   {
      mEngine->Kill();
      return EXIT_SUCCESS;
   }

   if(vm.count("list")) {
      const Engine::DevicePtrList& devices = mEngine->GetDevices();
      for(auto device = devices.begin(); device != devices.end(); device++) {
         std::cout << (*device)->getName() << " (" << (*device)->getDescription() << ")" << std::endl;
      }
      return EXIT_SUCCESS;
   }

   if(vm.count("sniff"))
   {
      std::string device = vm["sniff"].as<std::string>();
      mEngine->Sniff(device);
   }
   else
   {
       std::cerr << "No sniffing device specified" << std::endl;
       std::cout << desc << "\n";
       return EXIT_FAILURE;
   }
   
	return mEngine->Loop();
}
