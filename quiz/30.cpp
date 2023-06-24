#include <iostream>

using namespace std;

int main()
{
	int a = 5;
	int b = 0;
	int &r = a;
	r = b++;
	cout << a << r << b;
}
