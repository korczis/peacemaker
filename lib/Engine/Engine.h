//
//  Engine.h
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

#ifndef __peacemaker__Engine__
#define __peacemaker__Engine__

// core c++ includes
#include <memory>
#include <set>
#include <vector>

#include "../Packets/Packets.h"

namespace pm
{
   class Capture;
   class Device;
   
   class Engine
   {
   public:
      /**
       * @brief Constructor
       */
      Engine();
      
      /**
       * @brief destructor
       */
      virtual ~Engine();
      
      typedef std::shared_ptr<Capture> CapturePtr;
      typedef std::vector<Capture> CaptureList;
      typedef std::vector<CapturePtr> CapturePtrList;
      typedef std::set<CapturePtr> CaptureSet;
      
      typedef std::shared_ptr<Device> DevicePtr;
      typedef std::vector<Device> DeviceList;
      typedef std::vector<DevicePtr> DevicePtrList;
      
      /**
       * @brief Add capture to set managed by engine
       */
      inline Engine& AddCapture(CapturePtr capture)
      {
  	     mCaptures.insert(capture);
         return *this;
      }
      
      /**
       * @brief Remove capture from set managed by engine
       */
      inline Engine& RemoveCapture(CapturePtr capture)
      {
      	 mCaptures.erase(capture);
         return *this;
      }
      
      /**
       * @brief Get device by name
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
      
      /**
       * @brief Run engine loop
       */
      virtual int Loop();
      
      /**
       * @brief Sniff
       */
      void Sniff(const std::string& device);
      
   private:
      CaptureSet mCaptures;
      DevicePtrList mDevices;
   };
} /* namespace pm */

#endif /* defined(__peacemaker__Engine__) */
