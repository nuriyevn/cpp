//
// impl/StdCallbackFacilityImpl.hpp
//    real implementation of the default callback facility used by the
//    StdCallbackFacility template
//
// Copyright (c) 2010, Mathias Czichi
// this file is part of the brownie Libraries and distributed under the license
// described at the end of the file

#ifndef brownie_asynch_impl_StdCallbackFacilityImpl_hpp
#define brownie_asynch_impl_StdCallbackFacilityImpl_hpp

#include "../JobExecutor.hpp"
#include "LocalCallback.hpp"

namespace brownie {
namespace asynch {
namespace impl {

template <typename CallbackTarget_,
          typename LoggingFacility_,
          typename Allocator_>
class StdCallbackFacilityImpl {
   public:
      typedef CallbackTarget_                   CallbackTargetType;
      typedef brownie::asynch::JobExecutor      JobExecutorType;
      
   public:
      StdCallbackFacilityImpl(CallbackTargetType* pCallbackTarget)
      : mFacilities(pCallbackTarget) {
         mFacilities.logCtor(thisPtr(), pCallbackTarget);
      }
      
   public:
      void release() {
         mFacilities.logRelease(this);
         mFacilities.mpCallbackTarget = 0;
         examineDeferredRelease();
      }
      
      const bool isMarkedForRelease() const {
         return (mFacilities.mpCallbackTarget == 0);
      }
      
      CallbackTargetType* const getCallbackTarget() {
         return mFacilities.mpCallbackTarget;
      }
      
      JobExecutorType& jobExecutor() {
         return *mFacilities.mpJobExecutor;
      }
      
   public:
      template <typename Call_>
      bool allocateCall(Call_*& pCall) {
         const bool success = mFacilities.allocateCall(pCall);
            mFacilities.logAllocateCall(this, success, pCall);
            return success;
      }
      
      template <typename Call_>
      void freeCall(Call_* pCall) {
         mFacilities.logFreeCall(this, pCall);
         brownie::asynch::impl::localCallbackConcreteOperationCallDestructor(pCall);
         mFacilities.freeCall(pCall);
         examineDeferredRelease();
      }
      
      template <typename Notification_>
      bool allocateNotification(Notification_*& pNotification) {
         const bool success = mFacilities.allocateNotification(pNotification);
            mFacilities.logAllocateNotification(this, success, pNotification);
            return success;
      }
      
      template <typename Notification_>
      void freeNotification(Notification_* pNotification) {
         mFacilities.logFreeNotification(this, pNotification);
         brownie::asynch::impl::localCallbackConcreteNotificationDestructor(pNotification);
         mFacilities.freeNotification(pNotification);
         examineDeferredRelease();
      }
      
   private:
      void examineDeferredRelease() {
         if (isMarkedForRelease()) {
            if (!mFacilities.hasAllocations()) {
               mFacilities.logDeferredReleaseExamination(this, false);
               delete this;
            } else {
               mFacilities.logDeferredReleaseExamination(this, true);
            }
         }
      }
      
   private:
      ~StdCallbackFacilityImpl() {
         mFacilities.logDtor(this);
      }
      
   private:
      StdCallbackFacilityImpl* thisPtr() { return this; }
      
      struct Facilities
      : public LoggingFacility_
      , public Allocator_ {
         Facilities(CallbackTargetType* pCallbackTarget)
         : LoggingFacility_()
         , Allocator_()
         , mpJobExecutor(JobExecutorType::getInstance())
         , mpCallbackTarget(pCallbackTarget) { }
         
         JobExecutorType* mpJobExecutor;
         CallbackTargetType* mpCallbackTarget;
      }; // struct Facilities
      
      Facilities mFacilities;
}; // class StdCallbackFacilityImpl

} // namespace impl
} // namespace asynch
} // namespace brownie
#endif // brownie_asynch_impl_StdCallbackFacilityImpl_hpp

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
