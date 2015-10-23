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

	virtual string GetEventName(void)  const 
	{
		return this->event;	
	}

	virtual void Invoke (void) const
	{
		(this->listener->*this->action)();	
	};
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

template <typename ListenerType>
void EventDispatcher::RemoveEventListener ( string event, 
											ListenerType* listener,
											void (ListenerType::* action) (void))
{
	for (int key = 0; key < this->subscriptions.size(); ++key)
	{
		Subscription<ListenerType>* subsription = 
			dynamic_cast <Subscription <ListenerType>*> (this->subscription[key]);

		if (subscription && subscriptioin->listener == listener && subscription->action == action)
		{
			this->subscription.erase( this->subscriptions.begin() + key);
		};
	};
}

void EventDispatcher::DispatchEvent (const string event) const
{
	for (int key = 0; key < this->subscriptions.size(); key++)
	{
		if (this->subscriptions[key]->GetEventName() == event )
			this->subscriptions[key]->Invoke();
	};
};

class SubscriptionBase
{
public:
	virtual string GetEventName(void ) const
	{
	};
};

template <typename ListenerType> class Subsription : public SubscriptionBase
{
private:
	virtual string GetEventName(void ) const
	{
		return this->event;
	};
	virtual void Invoke(void) const
	{
	};

};

