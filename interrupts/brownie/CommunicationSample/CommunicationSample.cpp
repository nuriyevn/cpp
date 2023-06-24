// CommunicationTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>

#include "CalculatorConsumer.hpp"
#include "CalculatorConsumerB.hpp"


int _tmain(int argc, _TCHAR* argv[])
{
   printf("        Communication sample:\n");
   {  
      AcyncCalculator calc;
      CalculatorConsumer consumer(calc);

      consumer.doSample();
   }

   printf("        Brownie sample:\n");
   { 
      AcyncCalculatorB calc;
      CalculatorConsumerB consumer(calc);

      consumer.doSample();

      brownie::asynch::JobExecutor::getInstance()->run();
   }

   printf("\nPress any key to exit...\n");
   _getch();
	return 0;
}

