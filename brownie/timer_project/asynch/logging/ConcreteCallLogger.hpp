
namespace brownie {
namespace asynch {
namespace logging {

struct ConcreteCallLogger {
   void logCtor(void* pCall,
                void* pCallbackFacility);

   void logCtorArg(void* pCall,
                   void* pCallbackFacility,
                   const void* pArgument);

   void logCtorData(void* pCall,
                    void *pCallbackFacility,
                    const void* pData);

   void logCtorArgData(void* pCall,
                       void* pCallbackFacility,
                       const void* pArgument,
                       const void* pData);

   void logDtor(void* pCall);

   void logSendTo(void* pCall,
                  void* pCallee,
                  bool success);

   void logScheduleResult(void* pCall);

   void logResultCallback(void* pCall,
                          bool delivered);

   void logScheduleError(void* pCall);

   void logErrorCallback(void* pCall,
                         bool delivered);

   void logRelease(void* pCall,
                   bool deferr);
}; // struct LocalCallbackConcreteOperationCall

} // namespace logging
} // namespace asynch
} // namespace brownie
