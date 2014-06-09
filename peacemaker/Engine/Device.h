//
//  Device.h
//  peacemaker
//
//  Created by Tomas Korcak on 6/8/14.
//  Copyright (c) 2014 Tomas Korcak. All rights reserved.
//

#ifndef __peacemaker__Engine_Device__
#define __peacemaker__Engine_Device__

// core c++ includes
#include <memory>
#include <string>

#include "Engine.h"
#include "Capture.h"

namespace pm
{
   class Device
   {
   public:
      Device(const std::string& name = "", const std::string& description = "");
      virtual ~Device();
      
      typedef std::shared_ptr<Capture> CapturePtr;
      
      inline CapturePtr CreateCapture() const
      {
         return CreateCapture<Capture>();
      }
      
      template<typename T>
      inline std::shared_ptr<T> CreateCapture() const
      {
         return std::make_shared<T>(this->getName().c_str());
      }
      
      inline const std::string& getDescription() const
      {
         return mDescription;
      }
      
      inline Device& setDescription(const std::string& description) {
         mDescription = description;
         return *this;
      }
      
      inline const std::string& getName() const
      {
         return mName;
      }
      
      inline Device& setName(const std::string& name) {
         mName = name;
         return *this;
      }
      
   private:
      std::string mDescription;
      std::string mName;
   };
}; /* namespace pm */

#endif /* defined(__peacemaker__Engine_Device__) */
