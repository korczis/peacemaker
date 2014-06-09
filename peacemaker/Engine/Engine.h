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
#include <memory>
#include <vector>

namespace pm
{
   class Capture;
   class Device;
   
   class Engine
   {
   public:
      Engine();
      virtual ~Engine();
      
      typedef std::shared_ptr<Capture> CapturePtr;
      typedef std::vector<Capture> CaptureList;
      typedef std::vector<CapturePtr> CapturePtrList;
      
      typedef std::shared_ptr<Device> DevicePtr;
      typedef std::vector<Device> DeviceList;
      typedef std::vector<DevicePtr> DevicePtrList;
      
      inline Engine& AddCapture(CapturePtr capture)
      {
      	mCaptures.push_back(capture);
         return *this;
      }
      
      /**
       * Get device by name
       */
      const DevicePtr GetDevice(const char* name = NULL) const;
      
      /**
       * Get device by name
       */
      DevicePtr GetDevice(const char* name = NULL);
      
      /**
       * @brief Get internal list of devices
       */
      inline DevicePtrList& GetDevices()
      {
         return mDevices;
      }
      
      /**
       * @brief Get internal list of devices
       */
      inline const DevicePtrList& GetDevices() const
      {
         return mDevices;
      }
      
      /**
       * @brief Kill existing TCP connections
       */
      void Kill();
      
      /**
       * @brief List network devices
       */
      static size_t ListDevices(DevicePtrList& devices, bool include_any = true);
      
      virtual int Loop();
      
      /**
       * @brief Sniff
       */
      void Sniff(const std::string& device);
      
   private:
      CapturePtrList mCaptures;
      DevicePtrList mDevices;
   };
}; /* namespace pm */

#endif /* defined(__peacemaker__Engine__) */
