
#include "AcyncCalculatorB.hpp"
//-----------------------------------------------------------------------------
AcyncCalculatorB::AcyncCalculatorB()
   : mOperationCountNotification(0)
   , mOperationCount(0)
{
}
//-----------------------------------------------------------------------------
void AcyncCalculatorB::handleCall(AdditionCall& call)
{
   const CAdditionArgument &arg = call.getArgument();

   printf("Addition: %d %d\n", arg.first, arg.second);

   const int result = arg.first + arg.second;

   call.result().result = result;
   call.sendResult();

   mOperationCount++;
   if (mOperationCountNotification)
   {
      mOperationCountNotification->status().count = mOperationCount;
      mOperationCountNotification->sendStatus();
   }
}
//-------------------------------------------------------------------------------------------
void AcyncCalculatorB::handleCall(SubtractionCall& call)
{
   const CSubtractionArgument &arg = call.getArgument();

   printf("Subtraction: %d %d\n", arg.first, arg.second);

   const int result = arg.first - arg.second;

   call.result().result = result;
   call.sendResult();

   mOperationCount++;
   if (mOperationCountNotification)
   {
      mOperationCountNotification->status().count = mOperationCount;
      mOperationCountNotification->sendStatus();
   }
}
//-------------------------------------------------------------------------------------------
void AcyncCalculatorB::handleNotification(COperationCountNotification& notification)
{
   mOperationCountNotification = &notification;
   mOperationCountNotification->sendStatus();
}
//-------------------------------------------------------------------------------------------
void AcyncCalculatorB::handleDenotification(COperationCountNotification& notification)
{
   if (mOperationCountNotification && mOperationCountNotification == &notification)
   {
      mOperationCountNotification = 0;
      notification.sendDenotification();
   }
}
//-------------------------------------------------------------------------------------------
