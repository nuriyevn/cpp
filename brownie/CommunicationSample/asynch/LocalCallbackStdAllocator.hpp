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

#ifndef brownie_asynch_LocalCallbackStdAllocator_hpp
#define brownie_asynch_LocalCallbackStdAllocator_hpp

#include "log/LocalCallbackStdAllocator.hpp"

namespace brownie {
namespace asynch {

template <typename LoggingFacility_ = brownie::asynch::log::LocalCallbackStdAllocator>
struct LocalCallbackStdAllocator {
   LocalCallbackStdAllocator() // {{{
   : mFacilities() {
      mFacilities.logLocalCallbackStdAllocatorCtor(thisPtr());
   } // }}} LocalCallbackStdAllocator
   
   ~LocalCallbackStdAllocator() { // {{{
      mFacilities.logLocalCallbackStdAllocatorDtor(this);
   } // }}} ~LocalCalbackStdAllocator
   
   template <typename Call_>
   bool allocateCall(Call_*& pCall) { // {{{
      pCall = reinterpret_cast<Call_*>(new char[sizeof(Call_)]);
      mFacilities.logAllocateCall(this, pCall, sizeof(Call_));
      if (pCall != 0) {
         increaseAllocations();
      } else {
         mFacilities.logAllocateCallError(this, pCall, sizeof(Call_));
      }
      return (pCall != 0);
   } // }}} allocateCall
   
   template <typename Call_>
   void freeCall(Call_* pCall) { // {{{
      mFacilities.logFreeCall(this, pCall);
      delete[] reinterpret_cast<char*>(pCall);
      decreaseAllocations();
   } // }}} freeCall
   
   const bool hasAllocations() const { // {{{
      return (mFacilities.numAllocations() > 0);
   } // }}} hasAllocations
   
   void increaseAllocations() { // {{{
      mFacilities.increaseAllocations();
      mFacilities.logNumAllocations(this, mFacilities.numAllocations());
   } // }}} increaseAllocations
   
   void decreaseAllocations() { // {{{
      mFacilities.decreaseAllocations();
      mFacilities.logNumAllocations(this, mFacilities.numAllocations());
   } // }}} decreaseAllocations
   
   LocalCallbackStdAllocator* thisPtr() { return this; }
   
   struct Facilities
   : public LoggingFacility_ { // {{{
      Facilities()
      : LoggingFacility_()
      , mAllocations(0) { }
      
      void increaseAllocations() { mAllocations += 1; }
      void decreaseAllocations() { mAllocations -= 1; }
      const int numAllocations() const { return mAllocations; }
      int mAllocations;
   }; // }}} struct Facilities
   
   Facilities mFacilities;
}; // struct LocalCallbackStdAllocator

}; // namespace asynch
}; // namespace brownie
#endif // brownie_asynch_LocalCallbackStdAllocator_hpp
