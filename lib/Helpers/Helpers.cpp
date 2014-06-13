//
//  Helpers.cpp
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

#include "Helpers.h"

// core c++ includes
#include <cstdio>
#include <string>

using namespace pm;

std::string Helpers::IpToString(unsigned int ip)
{
	char buffer[16];
   
   unsigned char bytes[4];
   bytes[0] = ip & 0xFF;
   bytes[1] = (ip >> 8) & 0xFF;
   bytes[2] = (ip >> 16) & 0xFF;
   bytes[3] = (ip >> 24) & 0xFF;
   snprintf(buffer, sizeof(buffer), "%d.%d.%d.%d", bytes[3], bytes[2], bytes[1], bytes[0]);
   
   return std::string(buffer);
}