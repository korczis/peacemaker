//
//  PacketEthernet.h
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

#ifndef __peacemaker__PacketEthernet__
#define __peacemaker__PacketEthernet__

#include "Packet.h"

#include <cstdio>
#include <string>

namespace pm
{
   class PacketEthernet : public Packet
   {
   public:
      class Address
      {
      public:
         inline const unsigned char& operator[](int index) const
         {
            return data[index];
         }
         
         inline unsigned char& operator[](int index)
         {
            return data[index];
         }
         
         inline std::string ToString() const
         {
         	char tmp[18];
            sprintf(tmp, "%02X:%02X:%02X:%02X:%02X:%02X",
					data[0],
					data[1],
					data[2],
					data[3],
					data[4],
					data[5]
				);
            
            return std::string(tmp);
         }
         
      private:
         unsigned char data[6];
      };
      
      inline unsigned char* GetData()
      {
      	return ((unsigned char*)this) + sizeof(*this);
      }
      
      inline const unsigned char* GetData() const
      {
      	return ((const unsigned char*)this) + sizeof(*this);
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
      
      inline const Address& Src() const
      {
         return mSrc;
      }
      
      inline const Address& Dest() const
      {
         return mDest;
      }
      
      inline const unsigned short Type() const
      {
         return mType;
      }
      
   private:
      Address mDest;
      Address mSrc;
      unsigned short mType;
   }; // class PacketEthernet
}; /* namespace pm */

#endif /* defined(__peacemaker__PacketEthernet__) */
