#include <cstdlib>
#include <iostream>

using std::cout;
using std::endl;

struct A
{
	virtual ~A() {}
	virtual void foo() const
	{
		cout << "A::foo()" << endl;
	}
	virtual void bar() const
	{
		cout << "A::bar()" << endl;
	}
	void baz() const { cout << "A::baz()" << endl; }
 
};

struct B : public A
{
	virtual void foo() const 
	{
		cout << "B::foo()" << endl;
	}
	void bar() const 
	{
		cout << "B::bar()" << endl;
	}
	void baz() const
	{
		cout << "B::baz()" << endl;
	}
};

struct C : public B
{
	void foo() const
	{
		cout << "C::foo()" << endl;
	}
	void bar() const
	{
		cout << "C::bar()" << endl;
	}
	void baz() const
	{
		cout << "C::baz()" << endl;
	}
};

int main()
{
	cout << "pA is B:" << endl;
	A *pA = new B;
	pA->foo();
	pA->bar();
	pA->baz();
	delete pA;
	cout << "\npA is C:" << endl;
	pA = new C;
	pA->foo(); pA->bar(); pA->baz();
	delete pA;
	return EXIT_SUCCESS;
}

