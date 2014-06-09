//
//  Engine.cpp
//  peacemaker
//
//  Created by Tomas Korcak on 6/8/14.
//  Copyright (c) 2014 Tomas Korcak. All rights reserved.
//

#include "Engine.h"

#include "Capture.h"
#include "Device.h"

#include "../Logger/Logger.h"

using namespace pm;

// core c++ includes
#include <cstdlib>
#include <iostream>

// boost includes
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>

// pcap includes
#include <pcap.h>

Engine::Engine()
{
   Engine::ListDevices(mDevices);
}

Engine::~Engine()
{
   
}

Engine::DevicePtr Engine::GetDevice(const char* name)
{
   if(name == NULL)
   {
   	return mDevices.size() > 0 ? mDevices[0] : NULL;
   }
   
   for(auto device = mDevices.begin(); device != mDevices.end(); device++)
   {
      if((*device)->getName() == name) {
         return *device;
      }
   }
   
   return NULL;
}

const Engine::DevicePtr Engine::GetDevice(const char* name) const
{
   return const_cast<Engine*>(this)->GetDevice(name);
}

void Engine::Kill()
{
}

/* static */ size_t Engine::ListDevices(DevicePtrList& devices, bool include_any)
{
	size_t orig_size = devices.size();
   
   pcap_if_t *allDevices = NULL;
   char errbuf[PCAP_ERRBUF_SIZE];
   
   if(include_any)
   {
      devices.push_back(std::make_shared<Device>("any", "Pseudo device for access to all devices"));
   }
   
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
      devices.push_back(std::make_shared<Device>(device->name, description));
   }
   
   /* We don't need any more the device list. Free it */
   pcap_freealldevs(allDevices);
   
   return devices.size() - orig_size;
}

int Engine::Loop()
{
   return 0;
}

void Engine::Sniff(const std::string& device)
{
   Logger::Instance().Log("Engine::Sniff(\"" + device + "\")");
   
   Capture res(device.c_str());
   
   auto i = 1e7;
   while(--i)
   {
      boost::this_thread::sleep(boost::posix_time::microseconds(1));
   }
}
