#include "private/COnOffRootService.hpp"
#include "private/COnOffCalculatorClient.hpp"

class COnOffComponent : public CHBComponent
{
public:
	COnOffComponent();
	virtual ~COnOffComponent();
private:
	COnOffCalculatorClient mCalculatorClient;
	COnOffRootService mRootService;
};
