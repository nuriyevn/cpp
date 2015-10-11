#include <iostream>
using namespace std;

class Base
{
	public:
	virtual int f (const int &d)
	{ 
		return 2*d;
	}
	int CallFunction(const int &d)
	{
		return f(d) + 1;
	}
};

class Derived : public  Base
{
	public : 
		virtual int f(const int &d)
		{
			return d*d;
		}
		int CallFunction(const int &d)
		{
			return f(d) + 1;
		}
};

class B
{
	public:
		void print()
		{
			cout << "I'm B.print" << endl;
		}
};

class A
{
	public:
		void print()
		{
			cout << "I'm A.print()" << endl;
		}
};

int main()
{
	Base a;
	cout << a.CallFunction(5) << endl;
	Derived d;
	cout << d.CallFunction(5) << endl;
	
	return 0;
}

