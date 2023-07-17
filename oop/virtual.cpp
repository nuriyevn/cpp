#include <iostream>

class Base
{
public:
	Base() { std::cout << "Base:ctor()" << std::endl;}
	virtual ~Base()
	{
		std::cout << "~Base()" << std::endl;
	}
};

class Derived : public Base
{
public:	
    Derived() { std::cout << "Derived:ctor()" << std::endl;}
	~Derived()
	{
		std::cout << "~Derived()" << std::endl;
	}
};

int main()
{

	/* Base *obj[] = { new Base, new Derived, new Base};
	delete obj[0];
	delete obj[1];
	delete obj[2];	


	// https://stackoverflow.com/questions/252515/why-do-we-even-need-the-delete-operator
	Base *base =  new Base[3];
	//delete obj[0];
	//delete obj[1];
	//delete obj[2];
	delete[] base;   // okay?


    
	base = new Derived;
	delete base;*/

	Base *base = new Derived[3];
	delete[] base; // doesn't call Derived destrcutor


	Base *base3 = new Derived;

	delete base3;
};




