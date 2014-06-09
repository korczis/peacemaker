//
//  PacketUdp.h
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

#ifndef __peacemaker__PacketUdp__
#define __peacemaker__PacketUdp__

#include "Packet.h"

#include <arpa/inet.h>

namespace pm
{
   class PacketUdp : public Packet
   {
   public:
      inline unsigned short Sport() const
      {
         return ntohs(mSport);
      }
      
      inline unsigned short Dport() const
      {
         return ntohs(mDport);
      }
      
      inline unsigned short Length() const
      {
         return mLength;
      }
      
      inline unsigned short Checksum() const
      {
         return mChecksum;
      }
      
   private:
      unsigned short mSport; // Source port
      unsigned short mDport; // Destination port
      unsigned short mLength; // Datagram length
      unsigned short mChecksum; // Checksum
   }; // class PacketUdp
}; /* namespace pm */

#endif /* defined(__peacemaker__PacketUdp__) */
