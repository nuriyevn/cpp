#include "../LocalCallable.hpp"
#include "../LocalCallback.hpp"
#include "../impl/JobExecutor.cpp"
#include <iostream>
#include <cstdlib>
#include <time.h>

namespace brownie {
namespace asynch {
namespace test {

//----------------------------------------------------------------------------------------------
class CSimpleCallable
: public brownie::asynch::LocalCallable<CSimpleCallable> 
{
public:
   CSimpleCallable()
   : mNotification(0)
   {}
   //-------------------------------------------------------------------------------------------
   class CCallArgumentState1
   {
   public:
      CCallArgumentState1() : mArg(0) {}
      void setArg(const int arg) { mArg = arg; }
      int getArg() const { return mArg; }
   private:
      int mArg;
   };
   class CCallArgumentState2
   {
   public:
      CCallArgumentState2() : mArg(0) {}
      void setArg(const int arg) { mArg = arg; }
      int getArg() const { return mArg; }
   private:
      int mArg;
   };
   class CCallResult
   {
   public:
      CCallResult() : mRes(0) {}
      void setRes(const int res) { mRes = res; }
      int getRes() const { return mRes; }
   private:
      int mRes;
   };
   class CCallError
   {
   public:
      CCallError() : mErr(0) {}
      void setErr(const int err) { mErr = err; }
      int getErr() const { return mErr; }
   private:
      int mErr;
   };
   typedef brownie::asynch::FormalOperationCall<CCallArgumentState1, CCallResult, CCallError> tTestFormalOperationCall1;
   typedef brownie::asynch::FormalOperationCall<CCallArgumentState2, CCallResult, CCallError> tTestFormalOperationCall2;
   //-------------------------------------------------------------------------------------------
   class CNotificationStatus
   {
   public:
      CNotificationStatus() : mStat(0) {};
      void setStat(const int stat) { mStat = stat; };
      int getStat() const { return mStat; };
   private:
      int mStat;
   };
   typedef brownie::asynch::FormalNotification<CNotificationStatus> tFormalTestNotification;
   //-------------------------------------------------------------------------------------------
   void handleCall(tTestFormalOperationCall1& call)
   {
      const int val = call.getArgument().getArg();
      printf("*CSimpleCallable::handleCall<call1>(%i)\n", val);

      if (val < 5)
      {
         call.result().setRes(val);
         call.sendResult();
      }
      else
      {
         call.error().setErr(val);
         call.sendError();
      }

      if (mNotification)
      {
         mNotification->status().setStat(val);
         mNotification->sendStatus();
      }
   }
   //-------------------------------------------------------------------------------------------
   void handleCall(tTestFormalOperationCall2& call)
   {
      const int val = call.getArgument().getArg();
      printf("*CSimpleCallable::handleCall<call2>(%i)\n", val);

      if (val < 5)
      {
         call.result().setRes(val);
         call.sendResult();
      }
      else
      {
         call.error().setErr(val);
         call.sendError();
      }

      if (mNotification)
      {
         mNotification->status().setStat(val);
         mNotification->sendStatus();
      }
   }
   //-------------------------------------------------------------------------------------------
   void handleNotification(tFormalTestNotification& notification)
   {
      printf("*CSimpleCallable::handleNotification()\n");
      mNotification = &notification;
   }
   //-------------------------------------------------------------------------------------------
   void handleDenotification(tFormalTestNotification& notification)
   {
      printf("*CSimpleCallable::handleDenotification()\n");
      if (mNotification && mNotification == &notification)
      {
         mNotification = 0;
         notification.sendDenotification();
      }
   }
   //-------------------------------------------------------------------------------------------

private:
   tFormalTestNotification * mNotification;

};
//----------------------------------------------------------------------------------------------
class CSimpleCallback
: public brownie::asynch::LocalCallback<CSimpleCallback> 
{
public:
   CSimpleCallback(CSimpleCallable& callable)
   : mSimpleCallable(callable)
   , mConcreteNotification(0)
   {
      printf(" CSimpleCallback::CSimpleCallback()\n");
   }
   //-------------------------------------------------------------------------------------------
   typedef ConcreteOperationCall<CSimpleCallable::tTestFormalOperationCall1> tTestConcreteOperationCall1;
   void onResult(tTestConcreteOperationCall1& call)
   {
      printf(" CSimpleCallback::onResult<call1>(%i)\n", call.getResult().getRes());
   }
   void onError(tTestConcreteOperationCall1& call)
   {
      printf(" CSimpleCallback::onError<call1>(%i)\n", call.getError().getErr());
   }
   //-------------------------------------------------------------------------------------------
   typedef ConcreteOperationCall<CSimpleCallable::tTestFormalOperationCall2> tTestConcreteOperationCall2;
   void onResult(tTestConcreteOperationCall2& call)
   {
      printf(" CSimpleCallback::onResult<call2>(%i)\n", call.getResult().getRes());
   }
   void onError(tTestConcreteOperationCall2& call)
   {
      printf(" CSimpleCallback::onError<call2>(%i)\n", call.getError().getErr());
   }
   //-------------------------------------------------------------------------------------------
   typedef ConcreteNotification<CSimpleCallable::tFormalTestNotification> tTestConcreteNotification;
   void onStatus(tTestConcreteNotification& notification)
   {
	  printf("/==== Here is start of Status\n");
      printf(" CSimpleCallback::onStatus(%i)\n", notification.getStatus().getStat());

	  printf("/==== Here is end of Status\n");  

   }
   void onErrorStatus(tTestConcreteNotification& notification)
   {
      printf(" CSimpleCallback::onErrorStatus()\n");
   }
   void onDenotification(tTestConcreteNotification& notification)
   {
      printf(" CSimpleCallback::onDenotification()\n");
   }
   //-------------------------------------------------------------------------------------------
   void startNotification()
   {
      printf(" CSimpleCallback::startNotification()\n");

      // notification can be set in two ways:

      // first way:
      //if (!mConcreteNotification && createNotification(mConcreteNotification))
      //{
      //   mConcreteNotification->notifyAt(mSimpleCallable);
      //}

      // second way:
      if (!mConcreteNotification)
      {
         setNotification(mConcreteNotification, mSimpleCallable);
      }
   }
   //-------------------------------------------------------------------------------------------
   void stopNotification()
   {
      printf(" CSimpleCallback::stopNotification()\n");

      // denotification can be set in two ways also:

      // first way
      if (mConcreteNotification)
      {
         mConcreteNotification->denotify();
      }

      // second way
      //if (mConcreteNotification)
      //{
      //   removeNotification(mConcreteNotification);
      //}
   }
   //-------------------------------------------------------------------------------------------
   void call1(const int val)
   {
      printf(" CSimpleCallback::call1(%i)\n", val);
      tTestConcreteOperationCall1 * call = 0;
      if (createCall(call))
      {
         call->argument().setArg(val);
         call->sendTo(mSimpleCallable);
      }
   }
   //-------------------------------------------------------------------------------------------
   void call2(const int val)
   {
      printf(" CSimpleCallback::call2(%i)\n", val);
      tTestConcreteOperationCall2 * call = 0;
      if (createCall(call))
      {
         call->argument().setArg(val);
         call->sendTo(mSimpleCallable);
      }
   }
   //-------------------------------------------------------------------------------------------
private:
   CSimpleCallable& mSimpleCallable;
   tTestConcreteNotification * mConcreteNotification;

};
//----------------------------------------------------------------------------------------------
void runTest()
{
   printf("----- start -----\n");
   CSimpleCallable simpleCallable;
   CSimpleCallback simpleCallback(simpleCallable);
   simpleCallback.startNotification();
   //simpleCallback.stopNotification();

   printf("brownie::asynch::JobExecutor::getInstance()->run()\n{\n");
   brownie::asynch::JobExecutor::getInstance()->run();
   printf("}\n");
   simpleCallback.call1(1);
   simpleCallback.call2(2);
   printf("brownie::asynch::JobExecutor::getInstance()->run()\n{\n");
   brownie::asynch::JobExecutor::getInstance()->run();
   printf("}\n");
   simpleCallback.call1(3);
   simpleCallback.call2(4);
   simpleCallback.stopNotification();
   simpleCallback.call1(5);
   simpleCallback.call2(6);
   printf("brownie::asynch::JobExecutor::getInstance()->run()\n{\n");
   brownie::asynch::JobExecutor::getInstance()->run();
   printf("}\n");
   simpleCallback.call1(7);
   simpleCallback.call2(8);
   simpleCallback.call1(9);
   simpleCallback.call2(10);
   printf("brownie::asynch::JobExecutor::getInstance()->run()\n{\n");
   brownie::asynch::JobExecutor::getInstance()->run();
   printf("}\n");
   printf("----- stop -----\n");
}
//----------------------------------------------------------------------------------------------
}
}
}
//----------------------------------------------------------------------------------------------
int main(int argc, char* argv)
{
   brownie::asynch::test::runTest();
   return 0;
}
//----------------------------------------------------------------------------------------------
