#include <iostream>
using namespace std;
class EventDispatcher
{
public:
	template <typename ListenerType>
	void AddEventListener (
							string event,
							ListenerType *listener,
						  	void (ListenerType::* action) (void)):
private:
	vector <SubscriptionBase*> subscriptions;
						
};

template <typename ListenerType>
class Subscription : SubscriptionBase
{
private:
	string event;
	ListenerType *listener;
	void (ListenerType::* action) (void);
public:
	Subscription ( string event,
					ListenerType* listener,
					void (ListenerType::* action) (void)
				 )
	{
		this->event = event;	
		this->listener = listener;
		this->action = action;
	};
};


template <typename ListenerType>
void EventDispatcher::AddEventListener ( string event,
										ListenerType* listener,
										void (ListenerType::* action)(void))
{
	Subscription <ListenerType>* subscription = new Subscription <ListenerType> ( event,  listener, action);
	this->subscriptions.push_back(subscription);

};

class SubscriptionBase
{
};


