#include <iostream>
#include <algorithm>

int main()
{
	int myints[] = {10, 20, 30, 30, 20, 10, 10, 20};

	int *pbegin = myints;
	int *pend = myints + sizeof(myints)/sizeof(int);

	pend = std::remove (pbegin, pend, 20);

	std::cout << "range contains:";

	for (int *p = pbegin; p != pend; ++p)
	{
		std::cout << ' ' << *p;
	}

	std::cout << '\n';

	return 0;
}
	
