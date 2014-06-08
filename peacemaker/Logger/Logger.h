//
//  Logger.h
//  peacemaker
//
//  Created by Tomas Korcak on 6/8/14.
//  Copyright (c) 2014 Tomas Korcak. All rights reserved.
//

#ifndef __peacemaker__Logger__
#define __peacemaker__Logger__

#include <string>

namespace pm
{
   class Logger
   {
   public:
      Logger();
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
      
      const Logger& Info(const char* msg) const;
      const Logger& Info(const std::string& msg) const;

      const Logger& Log(const char* msg) const;
      const Logger& Log(const std::string& msg) const;
      
      const Logger& Warn(const char* msg) const;
      const Logger& Warn(const std::string& msg) const;      
   }; /* class Logger */
}; /* namespace pm */

#endif /* defined(__peacemaker__Logger__) */
