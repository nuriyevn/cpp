#ifndef brownie_asynch_task_SimpleTaskManager_hpp
#define brownie_asynch_task_SimpleTaskManager_hpp

namespace brownie {
namespace asynch {
namespace task {

template <typename TaskManagerTarget_>
class SimpleTaskManager {
   public:
      template <typename Task_,
                typename Call_>
      bool createTaskForCall(Task_*& pTask,
                             Call_& call) {
            pTask = new Task_(call, taskManagerTarget());
         const bool success = (pTask != 0);
            if (success) {
               pTask->start();
            }
            return success;
      }
      
      template <typename Task_>
      void taskFinished(Task_* pTask) {
         delete pTask;
      }
      
   private:
      TaskManagerTarget_& taskManagerTarget() { return static_cast<TaskManagerTarget_&>(*this); }
}; // class SimpleTaskManager

} // namespace task
} // namespace asynch
} // namespace brownie
#endif // brownie_asynch_task_SimpleTaskManager_hpp
