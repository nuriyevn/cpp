//
// logging/LocalCallable.hpp
//    default empty logging facility for the LocalCallable template
//
// Copyright (c) 2010, Mathias Czichi
// this file is part of the brownie Libraries and distributed under the license
// described at the end of the file

#ifndef brownie_asynch_logging_LocalCallable_hpp
#define brownie_asynch_logging_LocalCallable_hpp

namespace brownie {
namespace asynch {
namespace logging {

struct LocalCallable {
   void logCtor(void* pCallable,
                void* pCallableTarget) {
   }
   
   void logDtor(void* pCallable) {
   }
   
   void logScheduleCall(void* pCall,
                        void* pCallableTarget) {
   }
   
   void logOperationCall(void* pCall,
                         void* pCallableTarget) {
   }
   
   void logScheduleNotification(void* pNotification,
                                void* pCallableTarget) {
   }
   
   void logNotification(void* pNotification,
                        void* pCallableTarget) {
   }
   
   void logScheduleDenotification(void* pNotification,
                                  void* pCallableTarget) {
   }
   
   void logDenotification(void* pNotification,
                          void* pCallableTarget) {
   }
}; // struct LocalCallable

} // namespace logging
} // namespace asynch
} // namespace brownie
#endif // brownie_asynch_logging_LocalCallable_hpp

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
