#include <iostream>
#include <unistd.h>
#include "EventDispatcher.h"

using namespace std;

class Foo : public EventDispatcher
{
public:
	void Run(void)
	{
		for (int key = 0; key < 5; key++)
		{
			//cout << "Iteration " << key << endl;
			this->DispatchEvent("FOO_EVENT_1");
			this->DispatchEvent("FOO_EVENT_2");
			usleep(500000);
		};
	};
};

class Bar
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
	Bar *bar = new Bar();
	Foo *foo = new Foo();

	foo->AddEventListener ("FOO_EVENT_1", bar, &Bar::EventHandler1);
	foo->Run();

	foo->RemoveEventListener("FOO_EVENT_1", bar, &Bar::EventHandler1);
	foo->AddEventListener("FOO_EVENT_2", bar, &Bar::EventHandler2);
	foo->Run();


	delete foo;
	delete bar;	

	return 1;
}
