#include "CalculatorConsumer.hpp"
//-----------------------------------------------------------------------------
CalculatorConsumer::CalculatorConsumer(AcyncCalculator &calculator)
   : mCalculator(calculator)
{
}
//-----------------------------------------------------------------------------
void CalculatorConsumer::doSample()
{
   //subscription on attribute
   communication::OneArgFunction<const size_t&> operationCountSubscription = communication::bind(&CalculatorConsumer::printOperationCount, this);
   mCalculator.operationCount().subscribe( operationCountSubscription );

   //call with simple bind 
   mCalculator.addition(2, 4, communication::bind( &CalculatorConsumer::printResult, this) );

   //call with simple bind the same function
   mCalculator.subtraction(2, 4, communication::bind( &CalculatorConsumer::printResult, this) );

   //call with bind with user data
   mCalculator.addition(2, 4, communication::bind( &CalculatorConsumer::printResultWithExpectation, this, 8) );

   //unsubscribe
   mCalculator.operationCount().unsubscribe( operationCountSubscription );
}
//-----------------------------------------------------------------------------
void CalculatorConsumer::printOperationCount(const size_t &result)
{
   printf("OperationCount is: %d\n\n", result);
}
//-----------------------------------------------------------------------------
void CalculatorConsumer::printResult(int result)
{
   printf("Result is: %d\n", result);
}
//-----------------------------------------------------------------------------
void CalculatorConsumer::printResultWithExpectation(int result, int expectation)
{
   printf("Result is: %d. Expectation is: %d\n", result, expectation);
}
//-----------------------------------------------------------------------------
