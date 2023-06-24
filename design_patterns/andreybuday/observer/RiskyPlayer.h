#include "IObserver.h"

class RiskyPlayer : IObserver
{
public:
	string BoxerToPutMoneyOn;
	void Update(ISubject& subject);
};
