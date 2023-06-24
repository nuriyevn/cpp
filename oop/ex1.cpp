#include <iostream>
using namespace std;

class Base
{
public:
	int f(const int &d)
	{
		return 2*d;
	}
	int CallFunction(const int &d)
	{
		return f(d)+1;
	} 
};

class Derived: public Base
{
	public:
		int f(const int &d)
		{
			return d*d;
		}
};

int main()
{
	Base a;
	cout  << a.CallFunction(5) << endl;
	Derived b;
	cout << b.Derived::CallFunction(5) << endl;
	return 0;
}

