#include <cstdio>
#include <iostream>

int value = 9;

int main()
{
	int value = value;

	std::cout << value; // why 0? why not 9?
	return 0;
}
