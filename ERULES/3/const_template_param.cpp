#include <iostream>
using std::cout;
using std::cin;
using std::endl;

template <typename T>
void println(T* data)
{
	// Legal operation, however it's not useful in this, particular case
	// *data = 0;

	// Legal operation of redirecting pointer as template argument pointer 
	// is not const pointer

	int *new_data = new int;
	*new_data = 65;
	data = (T*)new_data;
	cout << *data << endl;
	delete new_data;
}

template <typename T>
void println_const(T* const data)
{
	// Again, legal operation	
	*data = 0;  // we can change content of pointer;

	// Illegal operation
	// int *new_data = new int;
	// *new_data = 65;
	// data = (T*)new_data; // we can't change the pointer itself
	// cout << *data << endl;
	// delete new_data;
}


int main()
{
	int i = 15;
	double pi =  3.14159;
	char c= 'H';

	//println_const(&i);
	//println_const(&pi);
	//println_const(&c);
	
	
	println(&i);
	println(&pi);
	println(&c);

	cout << "after nulling data" << endl;
	cout << i << endl;
	cout << pi << endl;
	cout << c << endl;
}



