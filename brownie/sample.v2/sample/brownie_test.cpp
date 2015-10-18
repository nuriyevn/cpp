#include <iostream>
//#include <cstdlib>

#include <windows.h>

#include "../asynch/LocalCallable.hpp"
#include "../asynch/LocalCallback.hpp"
#include "../asynch/impl/JobExecutor.cpp"

#include "./simpleCall.hpp"
#include "./simpleNotification.hpp"
#include "./thread.hpp"

static const int SLEEP_VALUE = 1000;
static const int NOTIFICATION_SLEEP_VALUE = 20000;

namespace brownie {
namespace asynch {
namespace test {

static CRITICAL_SECTION critSection;
static CRITICAL_SECTION critSectionLoop;

class JobThread
{
public:
   static JobThread* getInstance()
   {
      ::EnterCriticalSection(&critSection);
      if (mInstance == 0)
      {
         mInstance = new JobThread();
      }
      ::LeaveCriticalSection(&critSection);
      return mInstance;
   }

   DWORD start() 
   {
      mNeedStop = false;
      while (!mNeedStop)
      {
         ::EnterCriticalSection(&critSectionLoop);
         brownie::asynch::JobExecutor::getInstance()->run();
         ::LeaveCriticalSection(&critSectionLoop);
         ::Sleep(100);
      }

      return 0;
   };

   void stop() 
   {
      mNeedStop = true; 
   };

private:
   JobThread() : mNeedStop(false) {};
   JobThread(const JobThread& T) {};
   JobThread& operator=(const JobThread& T) {};

   static JobThread *mInstance;
   bool mNeedStop;
};

JobThread* JobThread::mInstance = 0;
}
}
}

using namespace brownie::asynch::test;
int main(int argc, char* argv)
{
   std::cout << "--------------------------------------------" << std::endl;
   std::cout << "Initial section" << std::endl;
   CSimpleCallCallable::CallArgument arg;

   ::InitializeCriticalSection(&brownie::asynch::test::critSection);
   ::InitializeCriticalSection(&brownie::asynch::test::critSectionLoop);
   Thread<JobThread> thread(JobThread::getInstance(), &JobThread::start);

   if (thread.start())
   {
	   /*
      // Примеры использования вызовов (Call)
      // Во всех примерах, отрицательный аргумент приводит к вызову onError.
      CSimpleCallCallable callable_call;
      CSimpleCallCallback callback_call(callable_call);

      // Используем только аргумент, обработки возвращаемого значения нет
      callback_call.DoCallWithArgument(10);
      Sleep(SLEEP_VALUE);

      callback_call.DoCallWithArgument(-10);
      Sleep(SLEEP_VALUE);

      // Используем только аргумент и createCallArg, обработки возвращаемого значения нет
      // Различие между createCall и createCallArg заключается в том, что когда используется
      // метод createCall, то аргумент для вызова создается с использованием конструктора 
      // по умолчанию. В случае использования createCallArg вместо использования конструктора 
      // по умолчанию для вргумента, используется конструктор копирования.
      arg.value = 20;
      callback_call.DoCallWithArgument(arg);
      Sleep(SLEEP_VALUE);

      arg.value = -20;
      callback_call.DoCallWithArgument(arg);
      Sleep(SLEEP_VALUE);

      // Используем аргумент с сохранением статуса между ассинхронными вызовами, обработки возвращаемого значения нет
      callback_call.DoCallWithArgumentAndData(30, 50);
      Sleep(SLEEP_VALUE);

      callback_call.DoCallWithArgumentAndData(-30, 50);
      Sleep(SLEEP_VALUE);

      // Вариант вызова созданного с использованием метода createCallData. 
      // Различие между createCall и createCallData заключается в том, что когда используется
      // метод createCall, то объект данных для вызова создается с использованием конструктора 
      // по умолчанию. В случае использования createCallData вместо использования конструктора 
      // по умолчанию для данных, используется конструктор копирования.
      callback_call.DoCallWithArgumentAndData(40);
      Sleep(SLEEP_VALUE);

      callback_call.DoCallWithArgumentAndData(-40);
      Sleep(SLEEP_VALUE);

      // То же самое, что и выше, только для создания вызова мы используем createCallArg
      arg.value = 50;
      callback_call.DoCallWithArgumentAndData(arg, 0);
      Sleep(SLEEP_VALUE);

      arg.value = -50;
      callback_call.DoCallWithArgumentAndData(arg, 0);
      Sleep(SLEEP_VALUE);

      // То же самое, что и выше, только для создания вызова мы используем createCallArgData
      // В этом примере для создания объектов аргумента и данных используются конструкторы
      // копирования
      arg.value = 60;
      callback_call.DoCallWithArgumentAndData(arg);
      Sleep(SLEEP_VALUE);

      arg.value = -60;
      callback_call.DoCallWithArgumentAndData(arg);
      Sleep(SLEEP_VALUE);

      //Вызовы с обработкой результата
      callback_call.DoCallWithArgumentAndResult(70);
      Sleep(SLEEP_VALUE);

      //Вызовы с обработкой результата и ошибки
      callback_call.DoCallWithArgumentResultAndError(80);
      Sleep(SLEEP_VALUE);

      callback_call.DoCallWithArgumentResultAndError(-80);
      Sleep(SLEEP_VALUE);
	  */
      CSimpleNotificationCallable callable_notification;
      CSimpleNotificationCallback callback_notification(callable_notification);

      Thread<CSimpleNotificationCallable> callable_thread(&callable_notification, &CSimpleNotificationCallable::start);
      if (callable_thread.start())
      {
         // Получаем метки времени
         callback_notification.subscribeSimpleNotification();
         Sleep(NOTIFICATION_SLEEP_VALUE);
         callback_notification.unsubscribeSimpleNotification();
   /*  
         // Получаем метки времени (текущее и предыдущее значения)
         callback_notification.subscribeSimpleDataNotification();
         Sleep(NOTIFICATION_SLEEP_VALUE);
         callback_notification.unsubscribeSimpleDataNotification();
      
         // Получаем метки времени со смещением на 50 лет
         callback_notification.subscribeArgumentNotification(50);
         Sleep(NOTIFICATION_SLEEP_VALUE);
         callback_notification.unsubscribeArgumentNotification();

         // Одновременная подписка на два сообщения (текущее время и со смещением на 50 лет)
         callback_notification.subscribeSimpleNotification();
         callback_notification.subscribeArgumentNotification(50);
         Sleep(NOTIFICATION_SLEEP_VALUE);
         callback_notification.unsubscribeSimpleNotification();
         callback_notification.unsubscribeArgumentNotification();
		 */

      }
   }
   Sleep(SLEEP_VALUE);
   brownie::asynch::test::JobThread::getInstance()->stop();
   thread.join();
   return 0;
}
