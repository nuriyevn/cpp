#include <iostream>

using namespace std;

void f(int (&a)[11])
{
	cout << sizeof(a) << endl;
}

int main()
{
	int a[10];
	cout << sizeof(a) << " ";
	f(a);
	return 0;
}
