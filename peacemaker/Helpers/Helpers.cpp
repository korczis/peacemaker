//
//  Helpers.cpp
//  peacemaker
//
//  Created by Tomas Korcak on 6/8/14.
//  Copyright (c) 2014 Tomas Korcak. All rights reserved.
//

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