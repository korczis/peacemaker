//
//  Application.h
//  peacemaker
//
//  Created by Tomas Korcak on 6/8/14.
//  Copyright (c) 2014 Tomas Korcak. All rights reserved.
//

#ifndef __peacemaker__Application__
#define __peacemaker__Application__

namespace pm
{
   class Engine;
   
   class Application
   {
   public:
      Application(const int& argc, const char** argv);
      virtual ~Application();
      
      // Generic application interface
      virtual int Run();
      
	private:
      const int& mArgc;
      const char**  mArgv;
      
      Engine* mEngine;
      
   }; /* class Application */
}; /* namespace pm */

#endif /* defined(__peacemaker__Application__) */
