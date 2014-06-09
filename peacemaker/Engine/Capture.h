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

#ifndef __peacemaker__Capture__
#define __peacemaker__Capture__

// core c++ includes
#include <string>

struct bpf_program;
struct pcap;
struct pcap_pkthdr;

namespace pm
{
   class Capture
   {
      Capture();
      Capture(const Capture& right);
      Capture& operator=(const Capture& right);
      
   public:
      /**
       * Constructor
       */
      Capture(const char* device);
      
      /**
       * Destructor
       */
      virtual ~Capture();
      
      typedef struct pcap* Handle;
      
      /**
       * @brief Processed buffered packets
       */
      virtual int Process(int count = -1);
      
      /**
       * Set capture filter
       */
      bool SetFilter(const char* filter, bool optimize = true, int netmask = 0);
      
      /**
       * Capture packet handler callback
       */
      virtual void Callback(const struct pcap_pkthdr *header, const unsigned char *data);
      
   private:
      const std::string mDevice;
      Handle mHandle;
      
      bpf_program* mFilter;
      
   }; /* class Capture */
}; /* namespace pm */

#endif /* defined(__peacemaker__Capture__) */
