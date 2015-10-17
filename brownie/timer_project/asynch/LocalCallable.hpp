//
// LocalCallable.hpp
//    C++ implementation of the callable concept for local execution units
//
// Copyright (c) 2010, Mathias Czichi
// this file is part of the brownie Libraries and distributed under the license
// described at the end of the file

#ifndef brownie_asynch_LocalCallable_hpp
#define brownie_asynch_LocalCallable_hpp

#include "FormalOperationCall.hpp"
#include "FormalNotification.hpp"
#include "JobExecutor.hpp"
#include "logging/LocalCallable.hpp"

namespace brownie {
namespace asynch {

template <typename CallableTarget_,
          typename LoggingFacility_ = brownie::asynch::logging::LocalCallable>
class LocalCallable {
   public:
      template <typename Argument_,
                typename Result_,
                typename Error_>
      void scheduleCall(FormalOperationCall<Argument_, Result_, Error_>& call) {
         mFacilities.logScheduleCall(&call, &callableTarget());
         jobExecutor().schedule(reinterpret_cast<JobExecutor::JobExecFunction>(DeferredOperationCall<FormalOperationCall<Argument_, Result_, Error_> >::doOperationCall), &call);
      }
      
      template <typename Value_,
                typename Argument_>
      void scheduleNotification(FormalNotification<Value_, Argument_>& notification) {
         mFacilities.logScheduleNotification(&notification, &callableTarget());
         jobExecutor().schedule(reinterpret_cast<JobExecutor::JobExecFunction>(DeferredNotificationCalls<FormalNotification<Value_, Argument_> >::doNotification), &notification);
      }
      
      template <typename Value_,
                typename Argument_>
      void scheduleDenotification(FormalNotification<Value_, Argument_>& notification) {
         mFacilities.logScheduleDenotification(&notification, &callableTarget());
         jobExecutor().schedule(reinterpret_cast<JobExecutor::JobExecFunction>(DeferredNotificationCalls<FormalNotification<Value_, Argument_> >::doDenotification), & notification);
      }
      
   protected:
      LocalCallable()
      : mFacilities() {
         mFacilities.logCtor(thisPtr(), &callableTarget());
      }
      
      // this destructor is useless and only exists to satisfy PCLint
      // todo: destructor has to be removed when memory has to be optimized, all classes inheriting from this have to use lint -e1510,1509 then!
      //
      // removed virtual modifier
      //
      //lint -eSym(1509,LocalCallable)
      ~LocalCallable() {
         mFacilities.logDtor(this);
      }
      
   private:
      template <typename FormalCall_>
      struct DeferredOperationCall {
         static void doOperationCall(FormalCall_* pCall) {
            CallableTarget_* pTarget = reinterpret_cast<CallableTarget_*>(pCall->getCalleePtr());
            LocalCallable* pCallable = pTarget;
               pCallable->mFacilities.logOperationCall(pCall, pTarget);
               pTarget->handleCall(*pCall);
         }
      }; // struct DeferredOperationCall
      
      template <typename FormalNotification_>
      struct DeferredNotificationCalls {
         static void doNotification(FormalNotification_* pNotification) {
            CallableTarget_* pTarget = reinterpret_cast<CallableTarget_*>(pNotification->getSubjectPtr());
            LocalCallable* pCallable = pTarget;
               pCallable->mFacilities.logNotification(pNotification, pTarget);
               pTarget->handleNotification(*pNotification);
         }
         
         static void doDenotification(FormalNotification_* pNotification) {
            CallableTarget_* pTarget = reinterpret_cast<CallableTarget_*>(pNotification->getSubjectPtr());
            LocalCallable* pCallable = pTarget;
               pCallable->mFacilities.logDenotification(pNotification, pTarget);
               pTarget->handleDenotification(*pNotification);
         }
      }; // struct DeferredNotificationCalls
      
   private:
      JobExecutor& jobExecutor() { return *mFacilities.mpJobExec; }
      LocalCallable* thisPtr() { return this; }
      CallableTarget_& callableTarget() { return static_cast<CallableTarget_&>(*this); }
      
      struct Facilities
      : public LoggingFacility_ {
         Facilities()
         : mpJobExec(JobExecutor::getInstance()) { }
         
         JobExecutor* mpJobExec;
      }; // struct Facilities
      
      Facilities mFacilities;
}; // class LocalCallable

} // namespace asynch
} // namespace brownie
#endif // brownie_asynch_LocalCallable_hpp

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
