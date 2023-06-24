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

#ifndef brownie_asynch_log_LocalCallback_hpp
#define brownie_asynch_log_LocalCallback_hpp

namespace brownie {
namespace asynch {
namespace log {

struct LocalCallback {
   void logCallbackFacilityCtor(void* pCallbackFacility,
                                void* pCallbackTarget) {
   }
   
   void logCallbackFacilityDtor(void* pCallbackFacility) {
   }
   
   void logCallbackFacilityRelease(void* pCallbackFacility,
                                   bool deferred) {
   }
   
   void logCallbackFacilityFree(void* pCallbackFacility) {
   }
   
   void logCallbackFacilityFreeCall(void* pCallbackFacility,
                                    void* pCall) {
   }
   
   void logConcreteOperationCallCtor(void* pCall,
                                     void* pCallbackFacility) {
   }
   
   void logConcreteOperationCallCtorArg(void* pCall,
                                        void* pCallbackFacility,
                                        const void* pArgument) {
   }
   
   void logConcreteOperationCallCtorData(void* pCall,
                                         void* pCallbackFacility,
                                         const void* pData) {
   }
   
   void logConcreteOperationCallCtorArgData(void* pCall,
                                            void* pCallbackFacility,
                                            const void* pArgument,
                                            const void* pData) {
   }
   
   void logConcreteOperationCallDtor(void* pCall) {
   }
   
   void logConcreteOperationCallRelease(void* pCall) {
   }
   
   void logConcreteOperationCallMarkForRelease(void* pCall) {
   }
   
   void logConcreteOperationCallSendTo(void* pCall,
                                       void* pCallee) {
   }
   
   void logConcreteOperationCallScheduleResult(void* pCall) {
   }
   
   void logConcreteOperationCallResultCallback(void* pCall,
                                               bool delivered) {
   }
   
   void logConcreteOperationCallScheduleError(void* pCall) {
   }
   
   void logConcreteOperationCallErrorCallback(void* pCall,
                                              bool delivered) {
   }
}; // struct LocalCallback

}; // namespace log
}; // namespace asynch
}; // namespace brownie
#endif // brownie_asynch_log_LocalCallback_hpp
