#include "CalculatorConsumerB.hpp"
//-----------------------------------------------------------------------------
CalculatorConsumerB::CalculatorConsumerB(AcyncCalculatorB &calculator)
   : mCalculator(calculator)
{
}
//-----------------------------------------------------------------------------
void CalculatorConsumerB::doSample()
{
   // start notification
   COperationCountConcreteNotification *operationCountSubscription = 0;
   setNotification(operationCountSubscription, mCalculator);

   { //simple call
      AdditionConcreteCall * call = 0;
      if (createCall(call))
      {
         call->argument().first = 2;
         call->argument().second = 4;
         call->sendTo(mCalculator);
      }
   }

   { //another simple call
      SubtractionConcreteCall * call = 0;
      if (createCall(call))
      {
         call->argument().first = 2;
         call->argument().second = 4;
         call->sendTo(mCalculator);
      }
   }

   { //simple call with user data
      AdditionConcreteWithDataCall * call = 0;
      if (createCall(call))
      {
         call->argument().first = 2;
         call->argument().second = 4;
         call->data().expectation = 8;
         call->sendTo(mCalculator);
      }
   }

   // stop notification
   //operationCountSubscription->denotify();
}
//-----------------------------------------------------------------------------
void CalculatorConsumerB::onStatus(COperationCountConcreteNotification& notification)
{
   printf("OperationCount is: %d\n\n", notification.getStatus().count);
}
//-----------------------------------------------------------------------------
void CalculatorConsumerB::onErrorStatus(COperationCountConcreteNotification& notification)
{
   printf("We do not use this.");
}
//-----------------------------------------------------------------------------
void CalculatorConsumerB::onDenotification(COperationCountConcreteNotification& notification)
{
   //hmmm
}
//-----------------------------------------------------------------------------
void CalculatorConsumerB::onResult(AdditionConcreteCall& call)
{
   printf("Result is: %d\n", call.getResult().result);
}
//-----------------------------------------------------------------------------
void CalculatorConsumerB::onError(AdditionConcreteCall& call)
{
   printf("We do not use this.");
}
//-----------------------------------------------------------------------------
void CalculatorConsumerB::onResult(SubtractionConcreteCall& call)
{
   printf("Result is: %d\n", call.getResult().result);
}
//-----------------------------------------------------------------------------
void CalculatorConsumerB::onError(SubtractionConcreteCall& call)
{
   printf("We do not use this.");
}
//-----------------------------------------------------------------------------
void CalculatorConsumerB::onResult(AdditionConcreteWithDataCall& call)
{
   printf("Result is: %d. Expectation is: %d\n", call.getResult().result, call.data().expectation);
}
//-----------------------------------------------------------------------------
void CalculatorConsumerB::onError(AdditionConcreteWithDataCall& call)
{
   printf("We do not use this.");
}
//-----------------------------------------------------------------------------
