#include "COnOffCalculatorClient.hpp"

COnOffRootService::COnOffRootService(COnOffCalculatorClient & calculatorClient)
	: HBApplication::CHBRootServiceStub()
	, mCalculatorClient(calculatorClient)
{

}

void COnOffRootService::requestBoot(const class CHBBootParameter &)
{
	TRC_SCOPE( onoff, COnOffRootService, requestBoot);
	mCalculatorClient.requestAdd(3, 4);
}
