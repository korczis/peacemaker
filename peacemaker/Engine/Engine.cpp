//
//  Engine.cpp
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
   int total = 0;
   while(true)
   {
      int count = 0;
      for(auto capture = mCaptures.begin(); capture != mCaptures.end(); capture++)
      {
         count += (*capture)->Process();
      }
      
      if(count == 0)
      {
   		boost::this_thread::sleep(boost::posix_time::milliseconds(10));
      }
   }
   
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
