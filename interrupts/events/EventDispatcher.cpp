#include "EventDispatcher.h"

void EventDispatcher::DispatchEvent(const string event) const
{
	for (int key = 0; key < this->subscriptions.size(); key++)
	{
		if (this->subscriptions[key]->GetEventName() == event)
			this->subscriptions[key]->Invoke();
	};
};
