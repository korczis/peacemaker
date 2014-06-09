//
//  Capture.h
//  peacemaker
//
//  Created by Tomas Korcak on 6/8/14.
//  Copyright (c) 2014 Tomas Korcak. All rights reserved.
//

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
      Capture(const char* device);
      virtual ~Capture();
      
      typedef struct pcap* Handle;
      
      virtual int Process(int count = -1);
      
      bool SetFilter(const char* filter, bool optimize = true, int netmask = 0);
      
      virtual void Callback(const struct pcap_pkthdr *header, const unsigned char *data);
      
   private:
      const std::string mDevice;
      Handle mHandle;
      
      bpf_program* mFilter;
      
   }; /* class Capture */
}; /* namespace pm */

#endif /* defined(__peacemaker__Capture__) */
