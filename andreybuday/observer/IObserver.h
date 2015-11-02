#include "ISubject.h"

class IObserver
{
public:
	virtual void Update(ISubject& subject) = 0;
};
