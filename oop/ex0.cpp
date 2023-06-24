#include <iostream>
using namespace std;

class base
{
	public:
		void start() {cout << "Base::start()\n";};
		void stop() {cout << "Base::stop()\n";};
		void doSomething() { start(); stop(); } 
		void f() {cout << "Base::f\n";}
};

class derived : public base
{
	public:
		void start() {cout << "Derived::start\n";};
		void stop() { cout << "Derived::stop\n";};
		void doSomething() { start(); stop();}
};


int main()
{
	base b;
	b.doSomething();

	derived d;
	d.doSomething();
	
}


