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

#ifndef brownie_asynch_impl_SimpleJobExecutor_hpp
#define brownie_asynch_impl_SimpleJobExecutor_hpp

#include "../Job.hpp"
#include <queue>

namespace brownie {
namespace asynch {

class JobExecutor {
   public:
      typedef void (*JobExecFunction)(void*);
      
   public:
      static JobExecutor* getInstance() {
         if (spInstance == 0) {
            spInstance = new JobExecutor();
         }
         return spInstance;
      }
      
   public:
      void schedule(JobExecFunction pFunction,
                    void* pArgs) {
         mJobs.push(JobExecInfo(pFunction, pArgs));
      }
      
      void schedule(Job* pJob) {
         schedule(execJob, pJob);
      }
      
   public:
      void run() {
         while (!mJobs.empty()) {
            JobExecInfo execInfo = mJobs.front();
               mJobs.pop();
               execInfo.execute();
         }
      }
      
   private:
      static void execJob(void* pArgs) {
         Job* pJob = reinterpret_cast<Job*>(pArgs);
            pJob->execute();
      }
      
   private:
      struct JobExecInfo {
         JobExecInfo(JobExecFunction pFunction,
                     void* pArgs)
         : mpFunction(pFunction), mpArgs(pArgs) { }
         
         void execute() {
            (*mpFunction)(mpArgs);
         }
         
         JobExecFunction mpFunction;
         void* mpArgs;
      }; // struct JobExecInfo
      
   private:
      JobExecutor()
      : mJobs() { }
      
      JobExecutor(const JobExecutor& src);
      JobExecutor& operator=(const JobExecutor& src);
      
   private:
      std::queue<JobExecInfo> mJobs;
      static JobExecutor* spInstance;
}; // class JobExecutor

} // namespace asynch
} // namespace brownie
#endif // brownie_asynch_impl_SimpleJobExecutor_hpp
