#include <iostream>
#include <cstdlib>

using namespace std;

class MyArray
{
public:
	MyArray() 
		: data(new int), size(1)
	{
		cout << "DEFAULT CTOR" << endl;
	}
	MyArray(int s) : data(new int[s]), size(s)
	{
		cout << "CUSTOM CTOR" << endl;	
	}
	MyArray(const MyArray& rhs)
		: data(new int[rhs.size]), size(rhs.size)
	{	
		cout << "COPY CTOR" << endl;
		std::copy(rhs.data, rhs.data + rhs.size, data);	
	}
	MyArray& operator=(const MyArray& rhs)
	{
		cout << "ASSIGNMENT CTOR" << endl;
		if (this != &rhs)
		{
			int *newdata = new int[rhs.size];
			std::copy(rhs.data, rhs.data + rhs.size,  newdata);
			delete [] data;
			data = newdata;
			size = rhs.size;
		}
		return *this;	
	}
	~MyArray()
	{	
		cout << "DTOR" << endl;
		delete [] data;
	}
	int& operator[](int index)
	{
		return data[index];
	}
	const int& operator[](int index) const
	{
		return data[index];
	}
private:
	int *data;
	int size;
};

int main()
{
	cout << "\nExpected CUSTOM. In fact: ";
	MyArray a(2);
	cout << "\nExcected CUSTOM. In fact: ";
	MyArray b(3);
	a[0] = 5, a[1] = 8;
	b[0] = 16, b[1] = 26, b[2] = 27;
	cout << "\nExpceted COPY. In fact: ";
	MyArray c(a);
	
	cout << "\nExpected COPY. In fact: "; 
	MyArray d = c;
	cout << "\nExpceted ASSIGNMENT. In fact: ";
	b = a;

	cout << "\nExpected 3xDEFAULT. In fact: ";
	MyArray ma[3];
	cout << "\nExpected 3xCUSTOM. In fact: ";
	MyArray ba[3]{{7},{7}, {7}}; // initializer-list
	
	cout << "b[0] = " << b[0] << endl;
	cout << "a[0] = " << a[0] << endl;
	cout << "c[0] = " << c[0] << endl;
	return 0; 		
}
