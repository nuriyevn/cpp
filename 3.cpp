#include <iostream>
// difference between passing array, fixed-sized array and base address of array as a function parameter

using namespace std;

// only use when the size of the array is relevant
void f(int (&a)[11])
{
	cout << sizeof(a) << endl;
}

// interesting template:
void func(const char str[10])
{
	cout << "specialize template for 10 itesm" <<  str << endl;
}

int main()
{
	int a[10];
	//cout << sizeof(a) << " ";
	// a reference of type "int (&)[11]" (not const-qualified) 
	// cannot be initialized with a value of type "int [10]"
	// f(a); 
	func("999999999");
	func("1010101010");
	func("test"); // Works.
	func("let's try something longer"); // Not a single f*ck given.
	return 0;
}
