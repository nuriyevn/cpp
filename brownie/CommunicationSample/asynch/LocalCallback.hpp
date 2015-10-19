//
// LocalCallback.hpp
//    asynchronous callback implementation for C++
//
// Copyright (c) 2010, Mathias Czichi
// this file is part of the brownie Libraries and distributed under the license
// described at the end of the file

#ifndef brownie_asynch_LocalCallback_hpp
#define brownie_asynch_LocalCallback_hpp

#include "FormalOperationCall.hpp"
#include "FormalNotification.hpp"
#include "StdCallbackFacility.hpp"
#include "StdNotificationAllocator.hpp"
#include "logging/LocalCallbackConcreteOperationCall.hpp"
#include "logging/LocalCallbackConcreteNotification.hpp"
#include "impl/DataHolder.hpp"
#include "impl/LocalCallback.hpp"

namespace brownie {
namespace asynch {

template <typename CallbackTarget_,
          typename CallbackFacility_ = StdCallbackFacility<CallbackTarget_> >
class LocalCallback {
   public:
      typedef CallbackTarget_                                        CallbackTargetType;
      typedef typename CallbackFacility_::CallbackFacilityType       CallbackFacilityType;

   public:
      template <typename FormalCall_,
                typename Data_ = brownie::common::Void,
                typename LoggingFacility_ = brownie::asynch::logging::LocalCallbackConcreteOperationCall>
      class ConcreteOperationCall
      : private FormalCall_
      , public brownie::asynch::impl::DataHolder<Data_> {
         public:
            typedef typename FormalCall_::ArgumentType               ArgumentType;
            typedef typename FormalCall_::ConstResultReturnType      ConstResultReturnType;
            typedef typename FormalCall_::ConstErrorReturnType       ConstErrorReturnType;
            typedef Data_                                            DataType;

         public:
            ArgumentType& argument() {
               return FormalCall_::mArgument;
            }

            const ArgumentType& argument() const {
               return FormalCall_::mArgument;
            }

            ConstResultReturnType getResult() {
               return FormalCall_::result();
            }

            ConstErrorReturnType getError() {
               return FormalCall_::error();
            }

         public:
            const bool isSent() const {
               return (FormalCall_::calleePtr() != 0);
            }

            template <typename Callable_>
            void sendTo(Callable_& callee) {
               if (!isSent()) {
                  mFacilities.logSendTo(this, &callee, true);
                  FormalCall_::calleePtr() = &callee;
                  callee.scheduleCall(formalCall());
               } else {
                  mFacilities.logSendTo(this, &callee, false);
               }
            }

            void release() {
               const bool deferr = isSent();
                  mFacilities.logRelease(this, deferr);
                  if (!deferr) {
                     mFacilities.mCallbackFacility.freeCall(this);
                  } else {
                     markForRelease();
                  }
            }

         private:
            static void scheduleResponse(void* pRawCall,
                                         bool result) {
               ConcreteOperationCall* pCall = reinterpret_cast<ConcreteOperationCall*>(pRawCall);
                  pCall->mFacilities.mResultResponse = result;

                  if (result) {
                     pCall->mFacilities.logScheduleResult(pCall);
                  } else {
                     pCall->mFacilities.logScheduleError(pCall);
                  }
                  pCall->mFacilities.mCallbackFacility.jobExecutor().schedule(responseCallback, pCall);
            }

            static void responseCallback(void* pRawCall) {
               ConcreteOperationCall* pCall = reinterpret_cast<ConcreteOperationCall*>(pRawCall);
               CallbackFacilityType& callbackFacility = pCall->mFacilities.mCallbackFacility;
               const bool deliver = ((!pCall->isMarkedForRelease()) &&
                                     (!callbackFacility.isMarkedForRelease()));
               const bool resultResponse = pCall->mFacilities.mResultResponse;
                  if (resultResponse) {
                     pCall->mFacilities.logResultCallback(pCall, deliver);
                  } else {
                     pCall->mFacilities.logErrorCallback(pCall, deliver);
                  }

                  if (deliver) {
                     if (resultResponse) {
                        callbackFacility.getCallbackTarget()->onResult(*pCall);
                     } else {
                        callbackFacility.getCallbackTarget()->onError(*pCall);
                     }
                  }

                  callbackFacility.freeCall(pCall);
            }

         private:
            ConcreteOperationCall(CallbackFacilityType& callbackFacility)
            : FormalCall_(thisPtr(),
                          scheduleResponse)
            , mFacilities(callbackFacility) {
               mFacilities.logCtor(thisPtr(), &callbackFacility);
            }

            ConcreteOperationCall(CallbackFacilityType& callbackFacility,
                                  const ArgumentType& argument)
            : FormalCall_(argument,
                          thisPtr(),
                          scheduleResponse)
            , mFacilities(callbackFacility) {
               mFacilities.logCtorArg(thisPtr(), &callbackFacility, &argument);
            }

            ConcreteOperationCall(const int marker,
                                  CallbackFacilityType& callbackFacility,
                                  const DataType& data)
            : FormalCall_(thisPtr(),
                          scheduleResponse)
            , brownie::asynch::impl::DataHolder<Data_>(data)
            , mFacilities(callbackFacility) {
               mFacilities.logCtorData(thisPtr(), &callbackFacility, &data);
            }

            ConcreteOperationCall(CallbackFacilityType& callbackFacility,
                                  const ArgumentType& argument,
                                  const DataType& data)
            : FormalCall_(argument,
                          thisPtr(),
                          scheduleResponse)
            , brownie::asynch::impl::DataHolder<Data_>(data)
            , mFacilities(callbackFacility) {
               mFacilities.logCtorArgData(thisPtr(), &callbackFacility, &argument, &data);
            }

         public://++
            ~ConcreteOperationCall() {
               mFacilities.logDtor(this);
            }

         private:
            const bool isMarkedForRelease() {
               return mFacilities.mMarkedForRelease;
            }

            void markForRelease() {
               mFacilities.mMarkedForRelease = true;
            }

         private:
            ConcreteOperationCall* thisPtr() { return this; }
            FormalCall_& formalCall() { return *this; }

            struct Facilities
            : public LoggingFacility_ {
               Facilities(CallbackFacilityType& callbackFacility)
               : LoggingFacility_()
               , mCallbackFacility(callbackFacility)
               , mResultResponse(false)
               , mMarkedForRelease(false) { }

               CallbackFacilityType& mCallbackFacility;
               bool mResultResponse;
               bool mMarkedForRelease;
            }; // struct Facilities

            Facilities mFacilities;

         private:
            ConcreteOperationCall(const ConcreteOperationCall& src);
            ConcreteOperationCall& operator=(const ConcreteOperationCall& src);

         friend class LocalCallback;

         //++template <typename ConcreteCall_>
         //++friend void brownie::asynch::impl::localCallbackConcreteOperationCallDestructor(ConcreteCall_* pCall);
      }; // class ConcreteOperationCall

   public:
      template <typename FormalNotification_,
                typename Data_ = brownie::common::Void,
                typename LoggingFacility_ = brownie::asynch::logging::LocalCallbackConcreteNotification,
                typename StatusAllocator_ = StdNotificationAllocator<typename FormalNotification_::ValueType> >
      class ConcreteNotification
      : private FormalNotification_
      , public brownie::asynch::impl::DataHolder<Data_> {
         public:
            typedef FormalNotification_                                    FormalNotification;
            typedef typename FormalNotification_::ValueType                ValueType;
            typedef typename FormalNotification_::ArgumentType             ArgumentType;
            typedef typename FormalNotification_::ArgumentReturnType       ArgumentReturnType;
            typedef typename FormalNotification_::ConstArgumentReturnType  ConstArgumentReturnType;
            typedef Data_                                                  DataType;

         public:
            const ValueType& getStatus() const {
               return *mFacilities.getReadPtr();
            }

            ArgumentReturnType argument() {
               return FormalNotification_::_argument();
            }

            ConstArgumentReturnType argument() const {
               return FormalNotification_::_argument();
            }

         public:
            const bool isNotified() const {
               return (FormalNotification_::subjectPtr() != 0);
            }

            template <typename Callable_>
            void notifyAt(Callable_& subject) {
               if (!isNotified()) {
                  mFacilities.logNotifyAt(this, &subject, true);
                  FormalNotification_::subjectPtr() = &subject;
                  mFacilities.mpDenotificationFunc = reinterpret_cast<DenotificationFunc>(DenotificationCaller<Callable_>::callDenotification);
                  subject.scheduleNotification(formalNotification());
               } else {
                  mFacilities.logNotifyAt(this, &subject, false);
               }
            }

            void denotify() {
               if (!isWaitingForDenotification()) {
                     mFacilities.logDenotify(this, true);
                  FormalNotification_* pFormalNotification = &formalNotification();
                  DenotificationFunc pDenotificationFunc = mFacilities.mpDenotificationFunc;
                     mFacilities.mpDenotificationFunc = 0;
                     (*pDenotificationFunc)(FormalNotification_::subjectPtr(), pFormalNotification);
               } else {
                  if (!isNotified()) {
                     mFacilities.logDenotify(this, true);
                     mFacilities.mCallbackFacility.freeNotification(this);
                  } else {
                     mFacilities.logDenotify(this, false);
                  }
               }
            }

         private:
            static void scheduleCallback(void* pRawNotification,
                                         bool status) {
               ConcreteNotification* pNotification = reinterpret_cast<ConcreteNotification*>(pRawNotification);

                  if (status) {
                     ValueType* pStatusValue;
                     const bool success = pNotification->mFacilities.allocateStatus(pStatusValue);
                        pNotification->mFacilities.logScheduleStatus(pNotification, success);

                        if (success) {
                           pNotification->statusValuePtr() = pStatusValue;
                           pNotification->mFacilities.mCallbackFacility.jobExecutor().schedule(reinterpret_cast<typename CallbackFacilityType::JobExecutorType::JobExecFunction>(statusCallback), pNotification);
                        } else {
                           pNotification->mFacilities.mCallbackFacility.jobExecutor().schedule(reinterpret_cast<typename CallbackFacilityType::JobExecutorType::JobExecFunction>(errorStatusCallback), pNotification);
                        }
                  } else {
                     pNotification->mFacilities.logScheduleDenotification(pNotification);
                     pNotification->mFacilities.mCallbackFacility.jobExecutor().schedule(reinterpret_cast<typename CallbackFacilityType::JobExecutorType::JobExecFunction>(denotificationCallback), pNotification);
                  }
            }

            static void statusCallback(ConcreteNotification* pNotification) {
               CallbackFacilityType& callbackFacility = pNotification->mFacilities.mCallbackFacility;
               const bool deliver = (!callbackFacility.isMarkedForRelease()) &&
                                    (!pNotification->isWaitingForDenotification());
                  pNotification->mFacilities.logStatusCallback(pNotification, deliver);
                  if (deliver) {
                     pNotification->mFacilities.nextStatus();
                     callbackFacility.getCallbackTarget()->onStatus(*pNotification);
                  } else {
                     if (!pNotification->isWaitingForDenotification()) {
                        pNotification->denotify();
                     }
                  }
            }

            static void errorStatusCallback(ConcreteNotification* pNotification) {
               CallbackFacilityType& callbackFacility = pNotification->mFacilities.mCallbackFacility;
               const bool deliver = (!callbackFacility.isMarkedForRelease()) &&
                                    (!pNotification->isWaitingForDenotification());
                  pNotification->mFacilities.logErrorStatusCallback(pNotification, deliver);
                  if (deliver) {
                     callbackFacility.getCallbackTarget()->onErrorStatus(*pNotification);
                  } else {
                     if (!pNotification->isWaitingForDenotification()) {
                        pNotification->denotify();
                     }
                  }
            }

            static void denotificationCallback(ConcreteNotification* pNotification) {
               CallbackFacilityType& callbackFacility = pNotification->mFacilities.mCallbackFacility;
               const bool deliver = (!callbackFacility.isMarkedForRelease()) &&
                                    (!pNotification->isWaitingForDenotification());
                  pNotification->mFacilities.logDenotificationCallback(pNotification, deliver);
                  if (deliver) {
                     callbackFacility.getCallbackTarget()->onDenotification(*pNotification);
                  }
                  callbackFacility.freeNotification(pNotification);
            }

         private:
            template <typename Subject_>
            struct DenotificationCaller {
               static void callDenotification(Subject_* pSubject,
                                              ConcreteNotification* pNotification) {
                  pSubject->scheduleDenotification(*pNotification);
               }
            }; // struct DenotificationCaller

            typedef void (*DenotificationFunc)(void*, FormalNotification_*);

         private:
            ConcreteNotification(CallbackFacilityType& callbackFacility)
            : FormalNotification_(thisPtr(),
                                  scheduleCallback)
            , mFacilities(callbackFacility) {
               mFacilities.logCtor(thisPtr(), &callbackFacility);
               FormalNotification_::statusValuePtr() = mFacilities.getWritePtr();
            }

         public:
            ~ConcreteNotification() {
               mFacilities.logDtor(this);
            }

         private:
            const bool isWaitingForDenotification() const {
               return (mFacilities.mpDenotificationFunc == 0);
            }

            const bool isInitialized() const {
               return (FormalNotification_::statusValuePtr() != 0);
            }

         private:
            ConcreteNotification* thisPtr() { return this; }
            FormalNotification_& formalNotification() { return *this; }

            struct Facilities
            : public LoggingFacility_
            , public StatusAllocator_ {
               Facilities(CallbackFacilityType& callbackFacility)
               : LoggingFacility_()
               , mCallbackFacility(callbackFacility)
               , mpDenotificationFunc(0) { }

               CallbackFacilityType& mCallbackFacility;
               DenotificationFunc mpDenotificationFunc;
            }; // struct Facilities

            Facilities mFacilities;

         private:
            ConcreteNotification(const ConcreteNotification& src);
            ConcreteNotification& operator=(const ConcreteNotification& src);

         friend class LocalCallback;

         //++template <typename ConcreteNotification_>
         //++friend void brownie::asynch::impl::localCallbackConcreteNotificationDestructor(ConcreteNotification_* pNotification);
      }; // class ConcreteNotification

   public:
      template <typename FormalCall_,
                typename Data_>
      bool createCall(ConcreteOperationCall<FormalCall_, Data_>*& pCall) {
         const bool success = callbackFacility().allocateCall(pCall);
            if (success) {
               new (static_cast<void*>(pCall)) ConcreteOperationCall<FormalCall_, Data_>(callbackFacility());
            }
            return success;
      }

      template <typename FormalCall_,
                typename Data_>
      bool createCallArg(ConcreteOperationCall<FormalCall_, Data_>*& pCall,
                         const typename FormalCall_::ArgumentType& argument) {
         const bool success = callbackFacility().allocateCall(pCall);
            if (success) {
               new (static_cast<void*>(pCall)) ConcreteOperationCall<FormalCall_, Data_>(callbackFacility(), argument);
            }
            return success;
      }

      template <typename FormalCall_,
                typename Data_>
      bool createCallData(ConcreteOperationCall<FormalCall_, Data_>*& pCall,
                          const Data_& data) {
         const bool success = callbackFacility().allocateCall(pCall);
            if (success) {
               new (static_cast<void*>(pCall)) ConcreteOperationCall<FormalCall_, Data_>(0, callbackFacility(), data);
            }
            return success;
      }

      template <typename FormalCall_,
                typename Data_>
      bool createCallArgData(ConcreteOperationCall<FormalCall_, Data_>*& pCall,
                             const typename FormalCall_::ArgumentType& argument,
                             const Data_& data) {
         const bool success = callbackFacility().allocateCall(pCall);
            if (success) {
               new (static_cast<void*>(pCall)) ConcreteOperationCall<FormalCall_, Data_>(callbackFacility(), argument, data);
            }
            return success;
      }

      template <typename Call_,
                typename Callee_>
      bool sendCall(Call_*& pCall,
                    Callee_& callee) {
         const bool success = createCall(pCall);
            if (success) {
               pCall->sendTo(callee);
            }
            return success;
      }

      template <typename Call_,
                typename Callee_>
      bool sendCallArg(Call_*& pCall,
                       const typename Call_::ArgumentType& argument,
                       Callee_& callee) {
         const bool success = createCallArg(pCall, argument);
            if (success) {
               pCall->sendTo(callee);
            }
            return success;
      }

      template <typename Call_,
                typename Callee_>
      bool sendCallData(Call_*& pCall,
                        const typename Call_::DataType& data,
                        Callee_& callee) {
         const bool success = createCallData(pCall, data);
            if (success) {
               pCall->sendTo(callee);
            }
            return success;
      }

      template <typename Call_,
                typename Callee_>
      bool sendCallArgData(Call_*& pCall,
                           const typename Call_::ArgumentType& argument,
                           const typename Call_::DataType& data,
                           Callee_& callee) {
         const bool success = createCallArgData(pCall, argument, data);
            if (success) {
               pCall->sendTo(callee);
            }
            return success;
      }

   public:
      template <typename FormalNotification_,
                typename Data_>
      bool createNotification(ConcreteNotification<FormalNotification_, Data_>*& pNotification) {
         bool success = callbackFacility().allocateNotification(pNotification);
            if (success) {
               new (static_cast<void*>(pNotification)) ConcreteNotification<FormalNotification_, Data_>(callbackFacility());
               success = pNotification->isInitialized();
               if (!success) {
                  callbackFacility().freeNotification(pNotification);
                  pNotification = 0;
               }
            }
            return success;
      }

      template <typename FormalNotification_,
                typename Data_,
                typename Subject_>
      bool setNotification(ConcreteNotification<FormalNotification_, Data_>*& pNotification,
                           Subject_& subject) {
         if (pNotification == 0) {
            if (createNotification(pNotification)) {
               pNotification->notifyAt(subject);
            } else {
               pNotification = 0;
            }
         }
         return (pNotification != 0);
      }

      template <typename ConcreteNotification_,
                typename Subject_>
      bool setNotificationData(ConcreteNotification_*& pNotification,
                               const typename ConcreteNotification_::DataType& data,
                               Subject_& subject) {
         if (pNotification == 0) {
            if (createNotification(pNotification)) {
               pNotification->data() = data;
               pNotification->notifyAt(subject);
            } else {
               pNotification = 0;
            }
         }
         return (pNotification != 0);
      }

      template <typename ConcreteNotification_,
                typename Subject_>
      bool setNotificationArg(ConcreteNotification_*& pNotification,
                              const typename ConcreteNotification_::ArgumentType& argument,
                              Subject_& subject) {
         if (pNotification == 0) {
            if (createNotification(pNotification)) {
               pNotification->argument() = argument;
               pNotification->notifyAt(subject);
            } else {
               pNotification = 0;
            }
         }
         return (pNotification != 0);
      }

      template <typename FormalNotification_,
                typename Data_>
      static
      void removeNotification(ConcreteNotification<FormalNotification_, Data_>*& pNotification) {
         if (pNotification != 0) {
            pNotification->denotify();
            pNotification = 0;
         }
      }

   public:
      template <typename Notification_>
      const typename Notification_::ValueType& getStatus(const Notification_* pNotification) const {
         if (pNotification != 0) {
            return pNotification->getStatus();
         } else {
            return impl::getEmptyStatus((typename Notification_::ValueType*)0);
         }
      }

   protected:
      LocalCallback()
      : mCallbackFacility(callbackTargetPtr()) {
      }

      // this destructor is useless and only exists to satisfy PCLint
      // it has been be removed to optimize memory
      //
      //lint -esym(1509, LocalCallback) suppress warning on all subcomponents
      //
      // removed destructor
      // virtual ~LocalCallback() {
      // }

   private:
      CallbackTarget_* const callbackTargetPtr() { return static_cast<CallbackTarget_*>(this); }
      CallbackFacilityType& callbackFacility() { return mCallbackFacility.callbackFacility(); }
      CallbackFacility_ mCallbackFacility;
}; // class LocalCallback

} // namespace asynch
} // namespace brownie
#endif // brownie_asynch_LocalCallback_hpp

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
