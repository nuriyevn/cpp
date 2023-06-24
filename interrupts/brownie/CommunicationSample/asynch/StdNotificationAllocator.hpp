//
// StdNotificationAllocator.cpp
//    ring buffer allocator for notification status delivery
//
// Copyright (c) 2010, Mathias Czichi
// this file is part of the brownie Libraries and distributed under the license
// described at the end of the file

#ifndef brownie_asynch_StdNotificationAllocator_hpp
#define brownie_asynch_StdNotificationAllocator_hpp

#include "logging/StdNotificationAllocator.hpp"
#include <cstring>
#include "impl/GeneralNotificationAllocator.hpp"

namespace brownie {
namespace asynch {

template <typename StatusType_,
          typename LoggingFacility_ = brownie::asynch::logging::StdNotificationAllocator,
          int MaxSizeBase_ = 4>
struct StdNotificationAllocator {
   StdNotificationAllocator()
   : mFacilities(new StatusType_(), new StatusType_()) {
      mFacilities.logCtor(thisPtr(), mFacilities.sMaxSize, (getWritePtr() != 0));
   }
   
   ~StdNotificationAllocator() {
      mFacilities.logDtor(this);
      for (int i=0; i<(Facilities::sMaxSize); i++) {
         if (mFacilities.mAllocations[i] != 0) {
            delete reinterpret_cast<StatusType_*>(mFacilities.mAllocations[i]);
         }
      }
   }
   
   StatusType_* const getReadPtr() const {
      return reinterpret_cast<StatusType_*>(mFacilities.getReadPtr());
   }
   
   StatusType_* const getWritePtr() const {
      return reinterpret_cast<StatusType_*>(mFacilities.getWritePtr());
   }
   
   bool allocateStatus(StatusType_*& pStatus) {
         pStatus = new StatusType_();
      const typename impl::GeneralNotificationAllocator<MaxSizeBase_>::AddResult result = mFacilities.addAllocatedStatus(pStatus);
      const bool success = (result == Facilities::Success);
         if (result == Facilities::AllocateError) {
            delete pStatus;
         }
         mFacilities.logAllocateStatus(this, success, mFacilities.mWriteIndex);
         return success;
   }
   
   void nextStatus() {
      delete getReadPtr();
      mFacilities.nextStatus();
      mFacilities.logNextStatus(this, mFacilities.mReadIndex);
   }
   
   StdNotificationAllocator* thisPtr() { return this; }
   
   struct Facilities
   : public impl::GeneralNotificationAllocator<MaxSizeBase_>
   , public LoggingFacility_ {
      Facilities(void* pReadObject,
                 void* pWriteObject)
      : impl::GeneralNotificationAllocator<MaxSizeBase_>(pReadObject, pWriteObject)
      , LoggingFacility_() {
      }
      
      ~Facilities() { }
   }; // struct Facilities
   
   Facilities mFacilities;
}; // struct StdNotificationAllocator

} // namespace asynch
} // namespace brownie
#endif // brownie_asynch_StdNotificationAllocator_hpp

// LICENSE
//
// brownie Libraries
// 
// Copyright (c) 2010, Mathias Czichi
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
// 
//    1) Redistributions of source code must retain the above copyright notice,
//       this list of conditions and the following disclaimer.
//       
//    2) Redistributions in binary form must reproduce the above copyright notice,
//       this list of conditions and the following disclaimer in the documentation
//       and/or other materials provided with the distribution.
//       
//    3) Neither the name of Mathias Czichi nor the names of its contributors may
//       be used to endorse or promote products derived from this software without
//       specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
