//
//  PacketIp.h
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

#ifndef __peacemaker__PacketIp__
#define __peacemaker__PacketIp__

#include "Packet.h"

#include <cstdint>

#include <arpa/inet.h>

#define IS_BIG_ENDIAN (!*(unsigned char *)&(uint16_t){1})

namespace pm
{
   class PacketIp : public Packet
   {
   public:
      class Address
      {
      public:
         inline std::string ToString() const
         {
         	char tmp[18];
            auto tmp_ip = *(unsigned int*)this; // ntohl(*(unsigned int*)this);
            const unsigned char* raw = (unsigned char*)&tmp_ip;
            sprintf(tmp, "%d.%d.%d.%d",
					raw[0],
					raw[1],
					raw[2],
					raw[3]
				);
            
            return std::string(tmp);
         }
         
      private:
      	unsigned char data[4];
      };
      
      inline unsigned char* GetData()
      {
      	return ((unsigned char*)this) + HeaderLength();
      }
      
      inline const unsigned char* GetData() const
      {
      	return ((const unsigned char*)this) + HeaderLength();
      }
      
      template<typename T>
      inline T* GetData()
      {
      	return (T*)GetData();
      }
      
      template<typename T>
      inline const T* GetData() const
      {
      	return (const T*)GetData();
      }
      
      inline unsigned char HeaderLength() const
      {
         return mHeaderLength * 4;
      }
      
      inline unsigned char Version() const
      {
         return mVersion;
      }
      
      inline unsigned int Whatever() const
      {
         return mWhatever;
      }
      
      inline unsigned short Offset() const
      {
         return mOffset;
      }
      
      inline unsigned char Ttl() const
      {
         return (unsigned char)mTtl;
      }
      
      inline unsigned char Prototocol() const
      {
         return (unsigned char)mProtocol;
      }
      
      inline unsigned short Checksum() const
      {
         return (unsigned short)mChecksum;
      }
      
      inline const Address& Src() const
      {
         return mSrc;
      }
      
      inline const Address& Dest() const
      {
         return mDest;
      }
      
   private:
#ifdef IS_BIG_ENDIAN
      /* type of service */
		unsigned char mHeaderLength : 4;
      
      /* version << 4 | header length >> 2 */
      unsigned char mVersion : 4;
#else
      /* version << 4 | header length >> 2 */
      unsigned char mVersion : 4;
      
      /* type of service */
		unsigned char mHeaderLength : 4;
#endif
      
      unsigned char mWhatever;
      
      /* total length */
		unsigned short mTotalLength;
      
      /* identification */
		unsigned int mId : 16;
      
      unsigned int mFlags : 3;
      
      /* fragment offset field */
		unsigned short mOffset : 13;

      /* time to live */
		unsigned int mTtl : 8;
      
      /* protocol */
		unsigned int mProtocol : 8;
      
      /* checksum */
		unsigned int mChecksum : 16;
      
      Address mSrc;
      
      Address mDest;
      
   }; // class PacketIp
}; /* namespace pm */

#endif /* defined(__peacemaker__PacketIp__) */
