
#include "AcyncCalculator.hpp"
//-----------------------------------------------------------------------------
AcyncCalculator::AcyncCalculator()
: mOperationCount(0, true, false)
{
}
//-----------------------------------------------------------------------------
void AcyncCalculator::addition(int first, int second, communication::OneArgFunction<int /*result*/> callback)
{
   printf("Addition: %d %d\n", first, second);

   const int result = first + second;

   callback.call(result);

   mOperationCount.set(mOperationCount.get() + 1);
}
//-----------------------------------------------------------------------------
void AcyncCalculator::subtraction(int first, int second, communication::OneArgFunction<int /*result*/> callback)
{
   printf("Subtraction: %d %d\n", first, second);

   const int result = first - second;

   callback.call(result);

   mOperationCount.set(mOperationCount.get() + 1);
}
//-----------------------------------------------------------------------------
