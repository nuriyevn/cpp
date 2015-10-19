
#include "MoCCAJobExecutor.hpp"

INIT_EVENT_STATICS(brownie::asynch::JobExecEvent);

namespace brownie {
namespace asynch {

JobExecutor::JobExecutor() {
   JobExecEvent::addListener(self());
}

JobExecutor::~JobExecutor() {
   JobExecEvent::removeListener(self());
}

JobExecutor* JobExecutor::getInstance() {
   JobExecutor* pExec = THBThreadLocalSingleton<JobExecutor>::getInstance();
      return pExec;
}

void JobExecutor::schedule(JobExecFunction pFunction,
                           void* pArgs) {
   JobExecEvent::sendEvent(JobExecData(this, pFunction, pArgs));
}

void JobExecutor::schedule(Job* pJob) {
   schedule(execJob, pJob);
}

void JobExecutor::execJob(void* pArgs)
{
   Job* pJob = reinterpret_cast<Job*>(pArgs);
   if( pJob )
   {
      pJob->execute();
   }
}

void JobExecutor::processEvent(const JobExecEvent& event) {
   if (event.data().mpJobExec == this) {
      (*event.data().mpExecFunc)(event.data().mpArgs);
   }
}

} // namespace asynch
} // namespace brownie
