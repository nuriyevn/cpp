//
// logging/LocalCallbackConcreteNotification.hpp
//    default empty logging facility for the nested ConcreteNotification class
//    of the LocalCallback template
//
// this file is part of the brownie Libraries and distributed under the license
// described at the end of the file

#ifndef brownie_asynch_logging_LocalCallbackConcreteNotification_hpp
#define brownie_asynch_logging_LocalCallbackConcreteNotification_hpp

namespace brownie {
namespace asynch {
namespace logging {

struct LocalCallbackConcreteNotification {
   void logCtor(void* pNotification,
                void* pCallbackFacility) {
   }
   
   void logDtor(void* pNotification) {
   }
   
   void logNotifyAt(void* pNotification,
                    void* pSubject,
                    bool success) {
   }
   
   void logDenotify(void* pNotification,
                    bool success) {
   }
   
   void logScheduleStatus(void* pNotification,
                          bool success) {
   }
   
   void logStatusCallback(void* pNotification,
                          bool delivered) {
   }
   
   void logErrorStatusCallback(void* pNotification,
                               bool delivered) {
   }
   
   void logScheduleDenotification(void* pNotification) {
   }
   
   void logDenotificationCallback(void* pNotification,
                                  bool delivered) {
   }
}; // struct LocalCallbackConcreteNotification

} // namespace logging
} // namespace asynch
} // namespace brownie
#endif // brownie_asynch_logging_LocalCallbackConcreteNotification_hpp

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
