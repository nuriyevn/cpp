#ifndef brownie_asynch_test_simplenotification
#define brownie_asynch_test_simplenotification

#include <iostream>
#include <ctime>
#include <windows.h>

#include "../asynch/LocalCallable.hpp"
#include "../asynch/LocalCallback.hpp"

namespace brownie {
namespace asynch {
namespace test {

class CSimpleNotificationCallable: public brownie::asynch::LocalCallable<CSimpleNotificationCallable> 
{
public:
   CSimpleNotificationCallable()
   : mSimpleNotification(0)
   , mArgumentNotification(0)
   {
   };

   struct NotificationStatus
   {
      NotificationStatus() : value(0) {};
      time_t value;
   };

   struct NotificationArgument
   {
      NotificationArgument() : value(0) 
      {
         std::cout << "NotificationArgument: Default constructor" << std::endl;
      };
      NotificationArgument(int val) : value(val) 
      {
         std::cout << "NotificationArgument: Constructor with value" << std::endl;
      };
      NotificationArgument(const NotificationArgument& val)
      {
         value = val.value;
         std::cout << "NotificationArgument: Copy constructor" << std::endl;
      };
      int value;
   };

   // ѕростой вариант сообщений, будем посылать текущее значение даты и времени
   typedef brownie::asynch::FormalNotification<NotificationStatus> SimpleNotification;

   void handleNotification(SimpleNotification& notification)
   {
      if (mSimpleNotification != 0)
      {
         mSimpleNotification->sendDenotification();
      }
      mSimpleNotification = &notification;
   }

   void handleDenotification(SimpleNotification& notification)
   {
      if (mSimpleNotification != 0)
      {
         mSimpleNotification->sendDenotification();
      }
      mSimpleNotification = 0;
   }

   // ¬ариант сообщений с аргументом, будем посылать значение даты и времени
   // сдвинутое на N лет относительно текущего (если -100 <= N <= 100)
   typedef brownie::asynch::FormalNotification<NotificationStatus, NotificationArgument> ArgumentNotification;

   void handleNotification(ArgumentNotification& notification)
   {
      if (mArgumentNotification != 0)
      {
         mArgumentNotification->sendDenotification();

      }
      mArgumentNotification = &notification;
   }

   void handleDenotification(ArgumentNotification& notification)
   {
      if (mArgumentNotification != 0)
      {
         mArgumentNotification->sendDenotification();
      }
      mArgumentNotification = 0;
   }

   // –ассылка сообщений производитс€ в отдельном потоке раз в 5 секунд
   DWORD start() 
   {
      mNeedStop = false;
      while (!mNeedStop)
      {
         time_t rawtime;
         time(&rawtime);
         
         if (mSimpleNotification != 0)
         {
            mSimpleNotification->status().value = rawtime;
            mSimpleNotification->sendStatus();
         }

         if (mArgumentNotification != 0)
         {
            struct tm timeinfo;
            localtime_s(&timeinfo, &rawtime);

            int mDt = mArgumentNotification->getArgument().value;
            if (mDt < -100) mDt = -100;
            else if (mDt > 100) mDt = 100;

            timeinfo.tm_year += mDt;
            rawtime = mktime(&timeinfo);
            mArgumentNotification->status().value = rawtime;
            mArgumentNotification->sendStatus();
         }

         ::Sleep(5000);
      }

      return 0;
   };

   void stop() 
   {
      mNeedStop = true; 
   };

private:
   bool mNeedStop;
   SimpleNotification* mSimpleNotification;
   ArgumentNotification* mArgumentNotification;
};


class CSimpleNotificationCallback: public brownie::asynch::LocalCallback<CSimpleNotificationCallback> 
{
public:
   CSimpleNotificationCallback(CSimpleNotificationCallable& callable)
   : mCallable(callable)
   , mMySimpleNotification(0)
   , mMySimpleDataNotification(0)
   , mMyArgumentNotification(0)
   {
   };

   // ѕростое сообщение
   typedef ConcreteNotification<CSimpleNotificationCallable::SimpleNotification> MySimpleNotification;

   void onStatus(MySimpleNotification& notification)
   {
      time_t rawtime = notification.getStatus().value;
      struct tm timeinfo;
      localtime_s(&timeinfo, &rawtime);
      std::cout << timeinfo.tm_mday << "-" << timeinfo.tm_mon << "-" << (timeinfo.tm_year + 1900)
         << " " << timeinfo.tm_hour << ":" << timeinfo.tm_min << ":" << timeinfo.tm_sec << std::endl;
   }

   void onErrorStatus(MySimpleNotification& notification)
   {
      std::cout << "Status Error MySimpleNotification" << std::endl;
   }

   void onDenotification(MySimpleNotification& notification)
   {
      std::cout << "Bye MySimpleNotification" << std::endl;
   }

   void subscribeSimpleNotification()
   {
      std::cout << "--------------------------------------------" << std::endl;
      std::cout << "Subscribe to the MySimpleNotification" << std::endl;
      setNotification(mMySimpleNotification, mCallable);
   }


   void unsubscribeSimpleNotification()
   {
      std::cout << "Unsubscribe from the MySimpleNotification" << std::endl;
      removeNotification(mMySimpleNotification);
   }

   // ѕростое сообщение с сохранением статуса
   typedef ConcreteNotification<CSimpleNotificationCallable::SimpleNotification, time_t> MySimpleDataNotification;

   void onStatus(MySimpleDataNotification& notification)
   {
      time_t rawtime1 = notification.data();
      struct tm timeinfo1;
      localtime_s(&timeinfo1, &rawtime1);
      
      time_t rawtime2 = notification.getStatus().value;
      struct tm timeinfo2;
      localtime_s(&timeinfo2, &rawtime2);

      notification.data() = rawtime2;

      std::cout << timeinfo1.tm_mday << "-" << timeinfo1.tm_mon << "-" << (timeinfo1.tm_year + 1900) << " " 
         << timeinfo1.tm_hour << ":" << timeinfo1.tm_min << ":" << timeinfo1.tm_sec << " -> "
         << timeinfo2.tm_mday << "-" << timeinfo2.tm_mon << "-" << (timeinfo2.tm_year + 1900) << " " 
         << timeinfo2.tm_hour << ":" << timeinfo2.tm_min << ":" << timeinfo2.tm_sec << std::endl;

   }

   void onErrorStatus(MySimpleDataNotification& notification)
   {
      std::cout << "Status Error MySimpleDataNotification" << std::endl;
   }

   void onDenotification(MySimpleDataNotification& notification)
   {
      std::cout << "Bye MySimpleDataNotification" << std::endl;
   }

   void subscribeSimpleDataNotification()
   {
      std::cout << "--------------------------------------------" << std::endl;
      std::cout << "Subscribe to the MySimpleDataNotification" << std::endl;

      time_t rawtime;
      time(&rawtime);
      setNotificationData(mMySimpleDataNotification, rawtime, mCallable);
   }

   void unsubscribeSimpleDataNotification()
   {
      std::cout << "Unsubscribe from the MySimpleNotification" << std::endl;
      removeNotification(mMySimpleDataNotification);
   }

   // Cообщение c аргументом
   typedef ConcreteNotification<CSimpleNotificationCallable::ArgumentNotification> MyArgumentNotification;

   void onStatus(MyArgumentNotification& notification)
   {
      time_t rawtime = notification.getStatus().value;
      struct tm timeinfo;
      localtime_s(&timeinfo, &rawtime);
      std::cout << timeinfo.tm_mday << "-" << timeinfo.tm_mon << "-" << (timeinfo.tm_year + 1900)
         << " " << timeinfo.tm_hour << ":" << timeinfo.tm_min << ":" << timeinfo.tm_sec << std::endl;
   }

   void onErrorStatus(MyArgumentNotification& notification)
   {
      std::cout << "Status Error MyArgumentNotification" << std::endl;
   }

   void onDenotification(MyArgumentNotification& notification)
   {
      std::cout << "Bye MyArgumentNotification" << std::endl;
   }

   void subscribeArgumentNotification(int val)
   {
      std::cout << "--------------------------------------------" << std::endl;
      std::cout << "Subscribe to the MyArgumentNotification" << std::endl;
      setNotificationArg(mMyArgumentNotification, CSimpleNotificationCallable::NotificationArgument(val), mCallable);
   }

   void unsubscribeArgumentNotification()
   {
      std::cout << "Unsubscribe from the MyArgumentNotification" << std::endl;
      removeNotification(mMyArgumentNotification);
   }

private:
   CSimpleNotificationCallable& mCallable;
   MySimpleNotification* mMySimpleNotification;
   MySimpleDataNotification* mMySimpleDataNotification;
   MyArgumentNotification* mMyArgumentNotification;
};

}
}
}

#endif //brownie_asynch_test_simplenotification