
#ifndef brownie_asynch_impl_MoCCAJobExecutor_hpp
#define brownie_asynch_impl_MoCCAJobExecutor_hpp

#include "../Job.hpp"
#include "api/sys/mocca/pf/comm/itc/src/THBEvent.hpp"
#include "api/sys/mocca/pf/core/oswrapper/src/THBThreadLocalSingleton.hpp"

namespace brownie {
namespace asynch {

typedef void (*__JobExecFunction__)(void*);
class JobExecutor;
class JobExecData {
   private:
      JobExecData(JobExecutor* const pJobExec,
                  __JobExecFunction__ pExecFunc,
                  void* pArgs)
      : mpJobExec(pJobExec), mpExecFunc(pExecFunc), mpArgs(pArgs) { }
      
      JobExecutor* mpJobExec;
      __JobExecFunction__ mpExecFunc;
      void* mpArgs;
      
   friend class JobExecutor;
}; // class JobExecData


DECLARE_EVENT(JobExecData, JobExecEvent, JobExecConsumer);


class JobExecutor
: public JobExecConsumer {
   public:
      typedef __JobExecFunction__   JobExecFunction;
   
   public:
      static JobExecutor* getInstance();
   
   public:
      void schedule(JobExecFunction pFunction,
                    void* pArgs);
      
      void schedule(Job* pJob);
      
   public:
      virtual void processEvent(const JobExecEvent& event);
      
      static void execJob(void* pArgs);
      
   private:
      JobExecutor& self() { return *this; }
      JobExecutor();
      virtual ~JobExecutor();
      
   friend class THBThreadLocalSingleton<JobExecutor>;
}; // class JobExecutor

} // namespace asynch
} // namespace brownie
#endif // brownie_asynch_impl_MoCCAJobExecutor_hpp
