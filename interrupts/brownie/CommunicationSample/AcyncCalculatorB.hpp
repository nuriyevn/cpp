#pragma once
//-----------------------------------------------------------------------------
#include "asynch\LocalCallable.hpp"
//-----------------------------------------------------------------------------
class AcyncCalculatorB 
   : public brownie::asynch::LocalCallable<AcyncCalculatorB> 
{
public:
   AcyncCalculatorB();

   class CAdditionArgument
   {
      public:
         int first;
         int second;
         CAdditionArgument() : first(0), second(0) {}
   };
   class CAdditionResult
   {
      public:
         int result;
         CAdditionResult() : result(0) {}
   };
   typedef brownie::asynch::FormalOperationCall<CAdditionArgument, CAdditionResult> AdditionCall;

   void handleCall(AdditionCall &call);


   class CSubtractionArgument
   {
      public:
         int first;
         int second;
         CSubtractionArgument() : first(0), second(0) {}
   };
   class CSubtractionResult
   {
      public:
         int result;
         CSubtractionResult() : result(0) {}
   };
   typedef brownie::asynch::FormalOperationCall<CSubtractionArgument, CSubtractionResult> SubtractionCall;

   void handleCall(SubtractionCall &call);


   class COperationCount
   {
   public:
      size_t count;

      COperationCount() : count(0) {}
   };
   typedef brownie::asynch::FormalNotification<COperationCount> COperationCountNotification;

   void handleNotification(COperationCountNotification& notification);
   void handleDenotification(COperationCountNotification& notification);

private:
   COperationCountNotification * mOperationCountNotification;
   size_t mOperationCount;
};
//-----------------------------------------------------------------------------
