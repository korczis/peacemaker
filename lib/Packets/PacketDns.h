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

#ifndef __peacemaker__PacketDns__
#define __peacemaker__PacketDns__

#include "Packet.h"

// core c++ includes
#include <cmath>
#include <cstring>
#include <string>

#include <arpa/inet.h>

namespace pm
{
   class PacketDns : public Packet
   {
   public:
      class Request
      {
      public:
         unsigned short GetType() const
         {
         	const char* data = (const char*)this;
            return ntohs(*(unsigned short*)(data+GetNameLength() + 1));
         }
         
         unsigned short GetClass() const
         {
         	const char* data = (const char*)this;
            return ntohs(*(unsigned short*)(data+GetNameLength() + 3));
         }
         
         std::string GetName(int offset = 0) const
         {
            std::string res;
            const char* data = (const char*)GetNameRaw();
            
            char buffer[256];
            
            int i = offset;
            while(data[i] != 0)
            {
               if(i != 0)
               {
                  res += ".";
               }
               
               int size = fmin(data[i], sizeof(buffer));
            	strncpy(buffer, data+i+1, size);
               buffer[size] = '\0';
               i += data[i] + 1;
               res += buffer;
            }
            
            return res;
         }
         
         int GetNameLength(int offset = 0) const
         {
            const char* data = (const char*)this;
            int i = offset;
            while(data[i] != 0)
            {
               i += data[i] + 1;
            }
            return i;
         }
         
         inline const unsigned char* GetNameRaw() const
         {
            return ((const unsigned char*)this);
         }
         
         inline int GetTotalLength() const
         {
            return GetNameLength() + 1 + sizeof(unsigned short) * 2;
         }
      };
      
      class Response
      {
      public:
         unsigned short GetType() const
         {
            return ntohs(mType);
         }
         
         unsigned short GetClass() const
         {
            return ntohs(mClass);
         }
         
         unsigned int GetTtl() const
         {
            return ntohl(mTtl);
         }
         
         unsigned short GetLength() const
         {
            return ntohs(mLength);
         }
         
      private:
         unsigned short mName;
         unsigned short mType;
         unsigned short mClass;
         unsigned int mTtl;
         unsigned short mLength;
      };
      
      const Request* GetRequest() const
      {
         return (Request*)((unsigned char*)this) + sizeof(*this);
      }
      
      const Response* GetResponse() const
      {
         const char* data = (const char*)GetRequest();
         return (const Response*)(data + GetRequest()->GetTotalLength());
      }
      
   	unsigned short Id;
      unsigned char Qr : 1;
      unsigned char Opcode : 4;
      unsigned char Aa : 1;
      unsigned char Tc : 1;
      unsigned char Rd : 1;
      unsigned char Ra : 1;
      unsigned char Z : 3;
      unsigned char Rcode : 4;
      unsigned short Qcount;
      unsigned short Ancount;
      unsigned short Nscount;
      unsigned short Arcount;
      
      
      
   }; // class PacketDns
}; /* namespace pm */

#endif /* defined(__peacemaker__PacketDns__) */
