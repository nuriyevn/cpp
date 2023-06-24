#ifndef __EVENT_DISPATCHER__
#define __EVENT_DISPATCHER__

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class SubscriptionBase
{
public:
	virtual string GetEventName(void) const { return ""; };
	virtual void  Invoke(void) const {};
};

template <typename ListenerType> 
class Subscription : public SubscriptionBase
{
private:
	virtual string GetEventName(void) const
	{
		return this->event;
	};
	virtual void Invoke (void ) const
	{
		(this->listener->*this->action) ();
	};
public:
	string event;
	ListenerType* listener;
	void (ListenerType::* action)(void);
	Subscription(string event, ListenerType* listener, void (ListenerType::* action) (void))
	{
		this->event = event;
		this->listener = listener;
		this->action = action;
	};
};

class EventDispatcher
{
private:
	vector <SubscriptionBase*> subscriptions;
protected:
	void DispatchEvent(const string event) const;
public:
	template <typename ListenerType>
	void AddEventListener(string, ListenerType*, void (ListenerType::*) (void));
	
	template <typename ListenerType>
	void RemoveEventListener(string, ListenerType* , void (ListenerType::*) (void));
};

template <typename ListenerType>
void EventDispatcher::AddEventListener(string event, ListenerType* listener, void (ListenerType::*action)(void))
{
	Subscription<ListenerType>* subscription = new Subscription<ListenerType> (event, listener, action);
	this->subscriptions.push_back(subscription);

};

template <typename ListenerType>
void EventDispatcher::RemoveEventListener(string event, ListenerType* listener, void (ListenerType::*action)(void))
{
	int key = 0;
	for (int key = 0; key < this->subscriptions.size(); ++key)
	{
		Subscription<ListenerType>* subscription = dynamic_cast <Subscription<ListenerType>*> (this->subscriptions[key]);
		if (subscription && subscription->listener && subscription->action == action)
		{
			this->subscriptions.erase(this->subscriptions.begin() + key);
		};
	};
}

#endif
