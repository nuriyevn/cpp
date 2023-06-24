#include <iostream>

struct A
{
	int m;
};

struct B
{
	~B();
	int m;
};

struct C
{
	C() : m()
	{
	}
	~C();
	int m;
};

sturct D: A
{
	D(int y): A(y) {}
	// D::D() is not declared because another constructor exists
}

int main()
{
		
}
