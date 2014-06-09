//
//  Logger.cpp
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