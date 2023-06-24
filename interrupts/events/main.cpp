#include <iostream>
#include <chrono>
#include <thread>

//#include <unistd.h>
#include "EventDispatcher.h"

using namespace std;

class MyEventDispatcher : public EventDispatcher
{
public:
	void Run(void)
	{
		for (int key = 0; key < 5; key++)
		{
			//cout << "Iteration " << key << endl;
			this->DispatchEvent("FOO_EVENT_1");
			this->DispatchEvent("FOO_EVENT_2");
			std::this_thread::sleep_for(std::chrono::microseconds(500000));
		};
	};
};

class MyListenerType
{
public:
	void EventHandler1(void)
	{
		cout << "FOO_EVENT_1 occured\n";
	};
	void EventHandler2(void)
	{
		cout << "FOO_EVENT_2 occured\n";
	};		
};

int main()
{
	MyListenerType *listener = new MyListenerType();
	MyEventDispatcher *dispatcher = new MyEventDispatcher();

	dispatcher->AddEventListener ("FOO_EVENT_1", listener, &MyListenerType::EventHandler1);
	dispatcher->Run();

	//foo->RemoveEventListener("FOO_EVENT_1", bar, &Bar::EventHandler1);
	dispatcher->AddEventListener("FOO_EVENT_2", listener, &MyListenerType::EventHandler2);
	dispatcher->Run();

	delete dispatcher;
	delete listener;	

	return 1;
}