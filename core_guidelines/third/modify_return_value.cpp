#include <iostream>
using std::cout;
using std::endl;

int sum(int a, int b)
{	
	int r = a + b;
	return r;
}

class Int
{
public:
	Int(int d)
		: data(d) {}
	Int& operator=(const Int& rhs)
	{
		data = rhs.data;
		return *this;
	}
	Int& add(const Int& b)
	{	
		data += b.data;
		return *this;
	}
	void print()
	{
		cout << "Data is " << data << endl;
	}


	~Int(){}
private:
	int data;
};



int main()
{
	int f = 7, s = 8;

//	sum(f, s) = 26; // illegal code, plain type of return value of function cannot be modified. 

	Int F(7);
	Int S(8);
	F.add(S) = 26; // legal code, we can modify the return value of the method of the user data type
	F.print();
}
