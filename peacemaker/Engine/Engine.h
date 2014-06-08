//
//  Engine.h
//  peacemaker
//
//  Created by Tomas Korcak on 6/8/14.
//  Copyright (c) 2014 Tomas Korcak. All rights reserved.
//

#ifndef __peacemaker__Engine__
#define __peacemaker__Engine__

// core c++ includes
#include <vector>

namespace pm
{
   class Engine
   {
   public:
      Engine();
      virtual ~Engine();
      
      // Engine device
      class Device;
      
      /**
       * @brief Kill existing TCP connections
       */
      void Kill();
      
      /**
       * @brief List network devices
       */
      static size_t ListDevices(std::vector<Device>& devices);
      
      /**
       * @brief Sniff
       */
      void Sniff(const std::string& device);
   };
}; /* namespace pm */

#endif /* defined(__peacemaker__Engine__) */
