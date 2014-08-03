//
//  Device.h
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
      /**
       * @brief Constructor
       */
      Device(const std::string& name = "", const std::string& description = "");
      
      /**
       * @brief Destructor
       */
      virtual ~Device();
      
      typedef std::shared_ptr<Capture> CapturePtr;
      
      /**
       * @brief Create default capture instance
       */
      inline CapturePtr CreateCapture() const
      {
         return CreateCapture<Capture>();
      }
      
      /**
       * @brief Create specific capture instance
       */
      template<typename T>
      inline std::shared_ptr<T> CreateCapture() const
      {
         return std::make_shared<T>(this->getName().c_str());
      }
      
      /**
       * Get device description
       */
      inline const std::string& getDescription() const
      {
         return mDescription;
      }
      
      /**
       * @brief Set device description
       */
      inline Device& setDescription(const std::string& description) {
         mDescription = description;
         return *this;
      }
      
      /**
       * @brief Get device name
       */
      inline const std::string& getName() const
      {
         return mName;
      }
      
      /**
       * @brief Set device name
       */
      inline Device& setName(const std::string& name) {
         mName = name;
         return *this;
      }
      
   private:
      std::string mDescription;
      std::string mName;
   };
} /* namespace pm */

#endif /* defined(__peacemaker__Engine_Device__) */
