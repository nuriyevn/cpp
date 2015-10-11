#include <iostream>
using namespace std;

struct Test
{
	Test() { cout << "Test()\n";}
   ~Test() { cout << "~Test()\n";}
};

int main()
{
	Test* t = new Test;
	delete t;
	return 0;

}
