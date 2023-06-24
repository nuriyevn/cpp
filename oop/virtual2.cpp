#include <iostream>
using namespace std;

class Base
{
public:
	virtual void someFunc() { cout << "Base::someFunc" << endl; }
	void someOtherFunc() { cout << "Base::someOtherFunc" << endl; }
};

class Derived : public Base
{
public:
	void someFunc() 
	{
		cout << "Derived::someFunc" << endl;
	}
};

int main()
{
	Base *b = new Derived();
	b->someFunc(); // Calls Derived::someFunc
	b->someOtherFunc(); // Calls Base::someOtherFunc();
}
