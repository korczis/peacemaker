//
//  Engine.cpp
//  peacemaker
//
//  Created by Tomas Korcak on 6/8/14.
//  Copyright (c) 2014 Tomas Korcak. All rights reserved.
//

#include "Engine.h"
#include "Device.h"

#include "../Logger/Logger.h"

using namespace pm;

// core c++ includes
#include <cstdlib>
#include <iostream>

// pcap includes
#include <pcap.h>

Engine::Engine()
{
   
}

Engine::~Engine()
{
   
}

void Engine::Kill()
{
}

/* static */ size_t Engine::ListDevices(std::vector<Engine::Device>& devices)
{
	size_t orig_size = devices.size();
   
   pcap_if_t *allDevices = NULL;
   char errbuf[PCAP_ERRBUF_SIZE];
   
   /* Retrieve the device list from the local machine */
   if (pcap_findalldevs(&allDevices, errbuf) == -1)
   {
      // fprintf(stderr,"Error in pcap_findalldevs: %s\n", errbuf);
      return 0;
   }
   
   /* Print the list */
   for(auto device = allDevices; device != NULL; device = device->next)
   {
      const char* description = device->description ? device->description : "No description available";
      devices.push_back(Device(device->name, description));
   }
   
   /* We don't need any more the device list. Free it */
   pcap_freealldevs(allDevices);
   
   return devices.size() - orig_size;
}

void Engine::Sniff(const std::string& device)
{
   Logger::Instance().Log("Engine::Sniff(\"" + device + "\")");
}
