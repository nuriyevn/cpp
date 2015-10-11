#include <iostream>

using namespace std;

struct A
{
	int i;
};

struct B: virtual  A 
{
	
};

struct C: virtual  A
{
};

struct D: B, C
{
};

int main()
{
	D d;
	d.i = 10;
	d.B::i = 10;
	d.C::i = 15;

	
};


