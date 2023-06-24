#include <iostream>
using namespace std;

class Clock
{
public:
	virtual void print() const 
	{
		cout << "Clock!" << endl;
	}
};

class Alarm: public Clock
{
public:
	virtual void print() const
	{
		cout << "Alarm!" << endl;
	}		
};

void settime(Clock &d)
{
	d.print();
}

int main()
{
	Clock W; // object of base class
	settime(W); // output Clock
	Alarm U;   // object of derived class
	settime(U); // reference to the derived class
	Clock *c1 = &W; // pointer to Clock object
	((Alarm*)c1)->print(); 
	c1 = &U; // pointer to Alarm object
	static_cast<Alarm*>(c1)->print(); 
}
