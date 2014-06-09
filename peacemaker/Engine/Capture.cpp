//
//  Capture.h
//  peacemaker
//
//  Created by Tomas Korcak on 6/8/14.
//  Copyright (c) 2014 Tomas Korcak. All rights reserved.
//

#include "Capture.h"

#include "../Logger/Logger.h"

using namespace pm;

// core c++ includes
#include <cstdlib>
#include <iostream>

// pcap includes
#include <pcap.h>

namespace  {
   static void Handler(u_char *user, const struct pcap_pkthdr *header, const u_char *data)
   {
      Capture* capture = (Capture*)user;
      capture->Callback(header, data);
   }
};

Capture::Capture(const char* device) : mDevice(device), mHandle(NULL), mFilter(NULL)
{
   char errbuf[PCAP_ERRBUF_SIZE];
   mHandle = pcap_open_live(device, 65536, 1, 1000, errbuf);
   
   mFilter = new bpf_program();
}

Capture::~Capture()
{
   if(mFilter)
   {
   	delete mFilter;
      mFilter = NULL;
   }
   
   if(mHandle)
   {
      pcap_close(mHandle);
      mHandle = NULL;
   }
}

/* virtual */ void Capture::Callback(const struct pcap_pkthdr *header, const unsigned char *data)
{
   Logger::Instance().Log("Capture::Callback() - Got packet!");
}

/* virtual */ int Capture::Process(int count /* = -1 */)
{
   return pcap_dispatch(mHandle, count, Handler, (unsigned char*)this);
}

bool Capture::SetFilter(const char *filter, bool optimize, int netmask)
{
   auto opt = optimize ? 1 : 0;
   auto res = pcap_compile(mHandle, mFilter, filter, opt, (bpf_u_int32)netmask);
   if(res != 0)
   {
      return false;
   }
   
   return pcap_setfilter(mHandle, mFilter) == 0;
}