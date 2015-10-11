#include "interface/CCalculatorClientBase.hpp"

class COnOffCalculatorClient : public CCalculatorClientBase
{
public:
	COnOffCalculatorClient(const char * rolename);
	virtual ~COnOffCalculatorClient();
	virtual void responseAdd(const int sum);
};
