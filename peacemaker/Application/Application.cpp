//
//  Application.cpp
//  peacemaker
//
//  Created by Tomas Korcak on 6/8/14.
//  Copyright (c) 2014 Tomas Korcak. All rights reserved.
//

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
      return 1;
   }

   if(vm.count("kill"))
   {
      mEngine->Kill();
   }

   if(vm.count("list")) {
      const Engine::DevicePtrList& devices = mEngine->GetDevices();
      for(auto device = devices.begin(); device != devices.end(); device++) {
         std::cout << (*device)->getName() << " (" << (*device)->getDescription() << ")" << std::endl;
      }
   }
   
   if(vm.count("sniff"))
   {
      std::string device = vm["sniff"].as<std::string>();
      mEngine->Sniff(device);
   }
   
	return mEngine->Loop();
}