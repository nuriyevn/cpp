//
// logging/LocalCallbackConcreteOperationCall.hpp
//    default empty logging facility for the nested ConcreteOperationCall class
//    of the LocalCallback template
//
// Copyright (c) 2010, Mathias Czichi
// this file is part of the brownie Libraries and distributed under the license
// described at the end of the file
//
// modified for usage in NBT
//

#ifndef brownie_asynch_logging_LocalCallbackConcreteOperationCall_hpp
#define brownie_asynch_logging_LocalCallbackConcreteOperationCall_hpp

#ifndef LOG_CONCRETE_CALLS
#include "EmptyConcreteCallLogger.hpp"
#else
#include "ConcreteCallLogger.hpp"
#endif // LOG_CONCRETE_CALLS

namespace brownie {
namespace asynch {
namespace logging {

#ifndef LOG_CONCRETE_CALLS
typedef EmptyConcreteCallLogger     LocalCallbackConcreteOperationCall;
#else
typedef ConcreteCallLogger          LocalCallbackConcreteOperationCall;
#endif // LOG_CONCRETE_CALLS

} // namespace logging
} // namespace asynch
} // namespace brownie
#endif // brownie_asynch_logging_LocalConcreteOperationCall_hpp

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
