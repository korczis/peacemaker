//
//  Logger.cpp
//  peacemaker
//
//  Created by Tomas Korcak on 6/8/14.
//  Copyright (c) 2014 Tomas Korcak. All rights reserved.
//

#include "Logger.h"

using namespace pm;

// core c++ includes
#include <iostream>

// boost includes
#include <boost/log/trivial.hpp>

Logger::Logger()
{
   
}

Logger::~Logger()
{
   
}

const Logger& Logger::Debug(const char* msg) const
{
   return Log(msg);
}

const Logger& Logger::Debug(const std::string& msg) const
{
   return Debug(msg.c_str());
}

const Logger& Logger::Error(const char* msg) const
{
   return Log(msg);
}

const Logger& Logger::Error(const std::string& msg) const
{
   return Error(msg.c_str());
}

const Logger& Logger::Info(const char* msg) const
{
   return Log(msg);
}

const Logger& Logger::Info(const std::string& msg) const
{
   return Info(msg.c_str());
}

const Logger& Logger::Log(const char* msg) const
{
   std::cout << msg << std::endl;
   return *this;
}

const Logger& Logger::Log(const std::string& msg) const
{
   return Log(msg.c_str());
}

const Logger& Logger::Warn(const char* msg) const
{
   return Log(msg);
}

const Logger& Logger::Warn(const std::string& msg) const
{
   return Warn(msg.c_str());
}