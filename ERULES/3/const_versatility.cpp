#include <iostream>
using std::cout;
using std::endl;
using std::cin;

char greeting[] = "Hello"; // non-const pointer, non-const data
char *p = greeting; // non-const pointer, non-const data
const char * cp = greeting; // const data, non-const pointer
const char * const ccp = greeting; // const data, const pointer
char const * const ccp2 = greeting; // alternative syntax for above

char * const p2 = greeting; // const pointer, non-const data

int main()
{

	char name[] = "Nusrat Nuriyev";

	p = name;
	p[0] = 'h';
	//cp[1] = 'a'; // illegal const data is constant
	cp = name; // legal
	//cp[1] = 'a'; // still can't modify data, no ma

	// Both of this are illegal
	//ccp = name;
	//ccp[1] = 'a';

	// legal
	p2[2] = 'L';
	p2[3] = 'L';
	// illegal
	//p2 = name;
}
