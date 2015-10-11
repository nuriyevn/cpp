#include <iostream>
#include <cstdlib>

using namespace std;

struct T
{
	T() :
	m(20)
	{	
		cout << "hello" << m << endl;
	}
private:
	int m;
};


int main()
{
	T t;
	return 0;
}
