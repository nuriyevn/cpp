#include <iostream>
using namespace std;
int main()
{
	int a = 0;
	for (;;)
	{
		cout << "1" << endl;
		if(a) break;
		a--;
	}
	cout << a;
}
