#pragma once
//-----------------------------------------------------------------------------
#include "AcyncCalculator.hpp"
//-----------------------------------------------------------------------------
class CalculatorConsumer
{
public:
   CalculatorConsumer(AcyncCalculator &calculator);

   void doSample();

private:
   AcyncCalculator &mCalculator;

   /*
   //Passing CleanableReference for class instead just pointer prevents calling callbacks after class was destroyed. 
   //If you are sure that this will not happen, you can use just pointer to class to bind to a callback.
   communication::CleanableReferenceMaster<CalculatorConsumer> mThisCleanable; //Move to another sample
   */

   void printOperationCount(const size_t &result);
   void printResult(int result);
   void printResultWithExpectation(int result, int expectation);
};
//-----------------------------------------------------------------------------
