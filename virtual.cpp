#include <iostream>

class Base
{
public:
	virtual ~Base()
	{
		std::cout << "Hello from ~Base()" << std::endl;
	}
};

class Derived : public Base
{
public:
	~Derived()
	{
		std::cout << "Hello from ~Derived()" << std::endl;
	}
};

int main()
{

	Base *obj[] = { new Base, new Derived, new Base};
	delete obj[0];
	delete obj[1];
	delete obj[2];	
};




