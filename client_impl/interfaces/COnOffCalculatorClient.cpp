#include "api/sys/mocca/pf/trace/src/HBTrace.h" //DBG_MSG
#include "api/sys/mocca/pf/appbase/application/base/src/HBApplication.hpp"
#include "interfaces/COnOffCalculatorClient.hpp"

TRC_SCOPE_DEF(onoff, COnOffCalculatorClient, responseAdd);

COnOffCalculatorClient :: COnOffCalculatorClient (const char *rolename)
	: CCalculatorClientBase(rolename)
{

}

void COnOffCalculatorClient::responseAdd(const int sum)
{
	TRC_SCOPE(onoff, COnOffCalculatorClient, responseAdd);
	if (7 == sum)
	{
		DBG_MSG(("3 + 4 is %d", sum));
	}
	else
	{
		DBG_MSG(("3 + 4 should be 7 but was %d", sum));
	}
	HBApplication::shutdown();
}
