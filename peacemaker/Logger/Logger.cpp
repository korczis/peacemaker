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
   BOOST_LOG_TRIVIAL(debug) << msg;
   return *this;
}

const Logger& Logger::Debug(const std::string& msg) const
{
   return Debug(msg.c_str());
}

const Logger& Logger::Error(const char* msg) const
{
   BOOST_LOG_TRIVIAL(error) << msg;
   return *this;
}

const Logger& Logger::Error(const std::string& msg) const
{
   return Error(msg.c_str());
}

const Logger& Logger::Fatal(const char* msg) const
{
   BOOST_LOG_TRIVIAL(fatal) << msg;
   return *this;
}

const Logger& Logger::Fatal(const std::string& msg) const
{
   return Fatal(msg.c_str());
}

const Logger& Logger::Info(const char* msg) const
{
   BOOST_LOG_TRIVIAL(info) << msg;
   return *this;
}

const Logger& Logger::Info(const std::string& msg) const
{
   return Info(msg.c_str());
}

const Logger& Logger::Log(const char* msg) const
{
   BOOST_LOG_TRIVIAL(info) << msg;
   return *this;
}

const Logger& Logger::Log(const std::string& msg) const
{
   return Log(msg.c_str());
}

const Logger& Logger::Warning(const char* msg) const
{
   BOOST_LOG_TRIVIAL(warning) << msg;
   return *this;
}

const Logger& Logger::Warning(const std::string& msg) const
{
   return Warning(msg.c_str());
}