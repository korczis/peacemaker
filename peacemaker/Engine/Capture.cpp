//
//  Capture.h
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
   pcap_set_promisc(mHandle, 1);
   
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

bool Capture::Inject(unsigned char* data, int len)
{
   return pcap_sendpacket(mHandle, data, len) == 0;
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