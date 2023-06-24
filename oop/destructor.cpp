#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

class Base
{
public:
	Base()
	{
		cout << "Base constructor" << endl;
	}
	~Base()
	{
		cout << "Base desctructor" << endl;
	}

};

class Derived : public Base
{
public:
	Derived()
	{
		cout << "Derived constructor!" << endl;
	}
	~Derived()
	{
		cout << "Derived desctructor!" << endl;
	}
};

class SuperDerived : public Derived
{
public:
	SuperDerived()
	{
		cout << "SuperDerived constructor!" << endl;
	}
	~SuperDerived()
	{
		cout << "SuperDerived destructor!" << endl;
	}
};

int main()
{
	Base *b = new SuperDerived();

	delete b;	
}
