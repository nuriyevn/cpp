
#include "ConcreteCallLogger.hpp"
#include "imp/nav/common/prj/nbt/trace/src/TraceExtension.hpp"

namespace brownie {
namespace asynch {
namespace logging {

LOGEXT_SCOPE_DEF(brownie, asynch, marble);

void ConcreteCallLogger::logCtor(void* pCall,
                                 void* pCallbackFacility) {
LOGEXT_SCOPE(brownie, asynch, marble);
   LOG_MSG(("MARBLE_CALL_CTOR:created call %p", pCall));
}

void ConcreteCallLogger::logCtorArg(void* pCall,
                                    void* pCallbackFacility,
                                    const void* pArgument) {
LOGEXT_SCOPE(brownie, asynch, marble);
   LOG_MSG(("MARBLE_CALL_CTOR:created call %p", pCall));
}

void ConcreteCallLogger::logCtorData(void* pCall,
                                     void *pCallbackFacility,
                                     const void* pData) {
LOGEXT_SCOPE(brownie, asynch, marble);
   LOG_MSG(("MARBLE_CALL_CTOR:created call %p", pCall));
}

void ConcreteCallLogger::logCtorArgData(void* pCall,
                                        void* pCallbackFacility,
                                        const void* pArgument,
                                        const void* pData) {
LOGEXT_SCOPE(brownie, asynch, marble);
   LOG_MSG(("MARBLE_CALL_CTOR:created call %p", pCall));
}

void ConcreteCallLogger::logDtor(void* pCall) {
LOGEXT_SCOPE(brownie, asynch, marble);
   LOG_MSG(("MARBLE_CALL_DTOR:destroyed call %p", pCall));
}

void ConcreteCallLogger::logSendTo(void* pCall,
                                   void* pCallee,
                                   bool success) {
LOGEXT_SCOPE(brownie, asynch, marble);
   LOG_MSG(("MARBLE_CALL_SEND:send call %p to %p", pCall, pCallee));
}

void ConcreteCallLogger::logScheduleResult(void* pCall) {
LOGEXT_SCOPE(brownie, asynch, marble);
   LOG_MSG(("MARBLE_CALL_RESULT_SEND:send result for call %p", pCall));
}

void ConcreteCallLogger::logResultCallback(void* pCall,
                                           bool delivered) {
LOGEXT_SCOPE(brownie, asynch, marble);
   LOG_MSG(("MARBLE_CALL_RESULT_CALLBACK:result callback for call %p", pCall));
}

void ConcreteCallLogger::logScheduleError(void* pCall) {
LOGEXT_SCOPE(brownie, asynch, marble);
   LOG_MSG(("MARBLE_CALL_ERROR_SEND:send error for call %p", pCall));
}

void ConcreteCallLogger::logErrorCallback(void* pCall,
                                          bool delivered) {
LOGEXT_SCOPE(brownie, asynch, marble);
   LOG_MSG(("MARBLE_CALL_ERROR_CALLBACK:error callback for call %p", pCall));
}

void ConcreteCallLogger::logRelease(void* pCall,
                                    bool deferr) {
}

} // namespace logging
} // namespace asynch
} // namespace brownie
