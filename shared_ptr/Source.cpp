#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Header.h"

using namespace std;

const char infoStr[] = {"INFO: THIS EXAMPLE EXPLAINS HOW\
TO CREATE UNIQUE POINTER AND MANIPULATE THEM\n"};

class TestData
{
public:
	TestData(){m_p = new int(100);}
	~TestData()
	{
		delete m_p;
		cout << "Destructor is called..." << endl;
	}
	int* GetData()
	{
		return m_p;
	}
	void Print()
	{
		cout << "Value = " << *m_p << endl;
	}
private:
	int *m_p;
};



void Fun1(unique_ptr<int> up)
{
	cout << "Value of up " << *up << endl;
}

void Fun2(unique_ptr<int>& up )
{
	cout << "Value of up = " << *up << endl;
}

template<class T>
void fun3(unique_ptr<T>& up)
{
	// After processing, say the pointer up is reset
	// reset calls the destructor of the resource
	up.reset();
}

void main
{
	// 1. Creating an unique pointer
	unique_ptr<int> up1 = unique_ptr<int>(new int(10));

	cout << " Value of up1 = " << *up1 << endl;	
	// 2.Assigning the unique pointer is not allowed
	// unique_ptr<int> up2 = up1;
	
	// 3. Copy constructor  is not  allowed. So cannot pass by vale to a function
	// Fun1(up1)

	// 4. But can pass byreference
	Fun2(up1);
	// 5. Getting raw pointer from the unique pointer
	int *p = up1.get();

	// 6. You can add the unique pointer to the vector
	std::vector<unique_ptr<int> > vecUp;
	//vecUp.push_back(up1);
	vecUp.push_back(std::move(up1));
	vecUp.push_back(unique_ptr<int>(new int(20)));
	vevUp.push_back(unique_ptr<int>(new int(30)));

	// After



}
























