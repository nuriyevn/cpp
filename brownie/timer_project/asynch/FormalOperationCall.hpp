//
// FormalOperationCall.hpp
//    implementation of the asynchronous operation call declaration concept
//    for C++
//
// this file is part of the brownie Libraries and distributed under the license
// described at the end of the file

#ifndef brownie_asynch_FormalOperationCall_hpp
#define brownie_asynch_FormalOperationCall_hpp

#include "impl/ResultHolder.hpp"
#include "impl/ErrorHolder.hpp"
#include "impl/OperationCommunicationFacility.hpp"
#include "../common/Void.hpp"

namespace brownie {
namespace asynch {

typedef brownie::asynch::impl::OperationCommunicationFacility  UnspecificOperationCall;

template <typename Argument_,
          typename Result_ = brownie::common::Void,
          typename Error_ = brownie::common::Void>
class FormalOperationCall
: public brownie::asynch::impl::ResultHolder<Result_>
, public brownie::asynch::impl::ErrorHolder<Error_>
, public brownie::asynch::impl::OperationCommunicationFacility {
   public:
      typedef Argument_                                                                      ArgumentType;
      typedef const Argument_&                                                               ConstArgumentReturnType;
      typedef Result_                                                                        ResultType;
      typedef typename brownie::asynch::impl::ResultHolder<Result_>::ResultReturnType        ResultReturnType;
      typedef typename brownie::asynch::impl::ResultHolder<Result_>::ConstResultReturnType   ConstResultReturnType;
      typedef Error_                                                                         ErrorType;
      typedef typename brownie::asynch::impl::ErrorHolder<Error_>::ErrorReturnType           ErrorReturnType;
      typedef typename brownie::asynch::impl::ErrorHolder<Error_>::ConstErrorReturnType      ConstErrorReturnType;
      
   public:
      ConstArgumentReturnType getArgument() const {
         return mArgument;
      } // getArgument
      
   protected:
      FormalOperationCall(void* pConcreteCall,
                          SendFunction pSendFunc)
      : OperationCommunicationFacility(pConcreteCall, pSendFunc)
      , mArgument() { }
      
      FormalOperationCall(const Argument_& argument,
                          void* pConcreteCall,
                          SendFunction pSendFunc)
      : OperationCommunicationFacility(pConcreteCall, pSendFunc)
      , mArgument(argument) { }
      
   protected:
      Argument_ mArgument;
      
   private:
      FormalOperationCall(const FormalOperationCall& src);
      FormalOperationCall& operator=(const FormalOperationCall& src);
}; // class FormalOperationCall

} // namespace asynch
} // namespace brownie
#endif // brownie_asynch_FormalOperationCall_hpp

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
