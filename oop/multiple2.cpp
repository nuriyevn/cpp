#include <iostream>

using namespace std;

class A 
{
public:
	virtual void f()
	{
		cout << "A::f()" << endl;
	}
};

class B
{
public:
	virtual void f()
	{
		cout << "B::f()" << endl;
	}
};

class C : public A,  public B 
{
/*public:
	void f()
	{
		cout << "C::f()" << endl;
	}
*/};


int main()
{
	C *pc = new C;
//	pc->f();
	pc->A::f();
	pc->B::f();
};

