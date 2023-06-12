#include <iostream>
using namespace std;
// interesting template:
template<unsigned int N>
void func(const char (&str)[N])
{
	cout << "generalized template for " << N << " elements: " <<  str << endl;
}

void func(const char (&str)[10])
{
	cout << "specialized template for 10 itesm" <<  str << endl;
}

int main()
{
    func("a");  
    func("ab");
    func("999999999");
	func("1010101010");
}
