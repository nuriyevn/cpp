#include <iostream>


template <typename T>
void f(const T& value)
{
	std::cout << value << std::endl;
}

template <typename T>
inline void callWithMax(const T& a, const T& b)
{
	f (a > b ? a : b);
}



int main()
{
	int a = 5;
	int b = 7;

	char c1 = 'A';
	char c2 = 'a';

	double pi = 3.14159;
	double e = 2.71;

	callWithMax(a, b);
	callWithMax(c1, c2);
	callWithMax(pi, e);

}
