//
//  Logger.h
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

#ifndef __peacemaker__Logger__
#define __peacemaker__Logger__

#include <string>

namespace pm
{
   class Logger
   {
   public:
      /**
       * @brief Constructor
       */
      Logger();
      
      /**
       * Destructor
       */
      virtual ~Logger();
      
      static Logger& Instance()
      {
      	static Logger instance;
         return instance;
      }
      
      const Logger& Debug(const char* msg) const;
      const Logger& Debug(const std::string& msg) const;
      
      const Logger& Error(const char* msg) const;
      const Logger& Error(const std::string& msg) const;
      
      const Logger& Fatal(const char* msg) const;
      const Logger& Fatal(const std::string& msg) const;
      
      const Logger& Info(const char* msg) const;
      const Logger& Info(const std::string& msg) const;

      const Logger& Log(const char* msg) const;
      const Logger& Log(const std::string& msg) const;
      
      const Logger& Warning(const char* msg) const;
      const Logger& Warning(const std::string& msg) const;
   }; /* class Logger */
}; /* namespace pm */

#endif /* defined(__peacemaker__Logger__) */
