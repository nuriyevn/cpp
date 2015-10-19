#pragma once
//-----------------------------------------------------------------------------
#include "AcyncCalculatorB.hpp"
#include "asynch/LocalCallback.hpp"
//-----------------------------------------------------------------------------
class CalculatorConsumerB
   : public brownie::asynch::LocalCallback<CalculatorConsumerB> 
{
public:
   CalculatorConsumerB(AcyncCalculatorB &calculator);

   void doSample();

public: //this really should be private, couse it is not for calling by user of this class
   typedef ConcreteOperationCall< AcyncCalculatorB::AdditionCall > AdditionConcreteCall;
   void onResult(AdditionConcreteCall& call);
   void onError(AdditionConcreteCall& call); 

   typedef ConcreteOperationCall< AcyncCalculatorB::SubtractionCall > SubtractionConcreteCall; 
   void onResult(SubtractionConcreteCall& call);
   void onError(SubtractionConcreteCall& call); 

   class AdditionData
   {
   public:
      int expectation;
      AdditionData() : expectation(0) {}
   };
   typedef ConcreteOperationCall< AcyncCalculatorB::AdditionCall, AdditionData > AdditionConcreteWithDataCall;
   void onResult(AdditionConcreteWithDataCall& call);
   void onError(AdditionConcreteWithDataCall& call); 


   typedef ConcreteNotification<AcyncCalculatorB::COperationCountNotification> COperationCountConcreteNotification;
   void onStatus(COperationCountConcreteNotification& notification);
   void onErrorStatus(COperationCountConcreteNotification& notification);
   void onDenotification(COperationCountConcreteNotification& notification);

private:
   AcyncCalculatorB &mCalculator;
};
//-----------------------------------------------------------------------------
