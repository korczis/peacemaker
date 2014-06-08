//
//  Device.cpp
//  peacemaker
//
//  Created by Tomas Korcak on 6/8/14.
//  Copyright (c) 2014 Tomas Korcak. All rights reserved.
//

#include "Device.h"

using namespace pm;

Engine::Device::Device(const std::string& name /* = "" */, const std::string& description /* = "" */) : mName(name), mDescription(description)
{
   
}

Engine::Device::~Device()
{
}
