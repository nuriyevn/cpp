#ifndef brownie_asynch_task_CallInducedTask_hpp
#define brownie_asynch_task_CallInducedTask_hpp

namespace brownie {
namespace asynch {
namespace task {

template <typename TaskTarget_,
          typename FormalCall_,
          typename TaskManager_>
class CallInducedTask {
   public:
      typedef FormalCall_                             FormalOperationCallType;
      typedef TaskManager_                            TaskManagerType;
      
   protected:
      CallInducedTask(FormalOperationCallType& call,
                      TaskManagerType& taskManager)
      : mCall(call)
      , mTaskManager(taskManager) { }
      
   protected:
      typename FormalCall_::ConstArgumentReturnType getArgument() const { return mCall.getArgument(); }
      
      typename FormalCall_::ResultReturnType result() { return mCall.result(); }
      typename FormalCall_::ConstResultReturnType result() const { return mCall.result(); }
      
      typename FormalCall_::ErrorReturnType error() { return mCall.error(); }
      typename FormalCall_::ConstErrorReturnType error() const { return mCall.error(); }
      
      FormalOperationCallType& getCall() { return mCall; }
      const FormalOperationCallType& getCall() const { return mCall; }
      
      TaskManagerType& taskManager() { return mTaskManager; }
      const TaskManagerType& taskManager() const { return mTaskManager; }
      
   protected:
      void sendResult() {
         getCall().sendResult();
         taskManager().taskFinished(taskTargetPtr());
      }
      
      void sendError() {
         getCall().sendError();
         taskManager().taskFinished(taskTargetPtr());
      }
      
   private:
      TaskTarget_* taskTargetPtr() { return static_cast<TaskTarget_*>(this); }
      FormalOperationCallType& mCall;
      TaskManagerType& mTaskManager;
}; // class CallInducedTask

} // namespace task
} // namespace asynch
} // namespace brownie
#endif // brownie_asynch_task_CallInducedTask_hpp
