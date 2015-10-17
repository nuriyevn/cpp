//
// FormalNotification.hpp
//    implementation of the asynchronous notification declaration concept
//    for C++
//
// this file is part of the brownie Libraries and distributed under the license
// described at the end of the file

#ifndef brownie_asynch_FormalNotification_hpp
#define brownie_asynch_FormalNotification_hpp

#include "../common/Void.hpp"
#include "impl/ArgumentHolder.hpp"
#include "impl/NotificationCommunicationFacility.hpp"

namespace brownie {
namespace asynch {

typedef brownie::asynch::impl::NotificationCommunicationFacility  UnspecificNotification;

template <typename Value_,
          typename Argument_ = brownie::common::Void>
class FormalNotification
: public brownie::asynch::impl::NotificationCommunicationFacility
, public brownie::asynch::impl::ArgumentHolder<Argument_> {
   public:
      typedef Value_                         ValueType;
      typedef Argument_                      ArgumentType;
      typedef typename brownie::asynch::impl::ArgumentHolder<Argument_>::ArgumentReturnType        ArgumentReturnType;
      typedef typename brownie::asynch::impl::ArgumentHolder<Argument_>::ConstArgumentReturnType   ConstArgumentReturnType;
      
   public:
      ValueType& status() {
         return (*reinterpret_cast<ValueType*>(statusValuePtr()));
      }
      
      const ValueType& status() const {
         return (*reinterpret_cast<ValueType*>(statusValuePtr()));
      }
      
      ConstArgumentReturnType getArgument() const {
         return brownie::asynch::impl::ArgumentHolder<Argument_>::_argument();
      }
   
   protected:
      FormalNotification(void* pConcreteCall,
                         SendFunction pSendFunc)
      : NotificationCommunicationFacility(pConcreteCall,
                                          pSendFunc) { }
      
      FormalNotification(const Argument_& argument,
                         void* pConcreteCall,
                         SendFunction pSendFunc)
      : NotificationCommunicationFacility(pConcreteCall,
                                          pSendFunc)
      , brownie::asynch::impl::ArgumentHolder<Argument_>(argument) { }
      
   private:
      FormalNotification(const FormalNotification& src);
      FormalNotification& operator=(const FormalNotification& src);
}; // class FormalNotification

} // namespace asynch
} // namespace brownie
#endif // brownie_asynch_FormalNotification_hpp

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
