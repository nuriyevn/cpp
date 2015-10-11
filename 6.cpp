#include <iostream>

using namespace std;

class A
{
	public:
		A();
		friend A &operator+(A &, const int);
		int getValue() const;
	private:
		int val;
};

A::A() { val = 0; }
int A::getValue() const  { return val; }

A& operator+ (A &sa, const int a)
{	
sa.val += a;
	return sa;
} 

int main()
{
	A q, w;
	w + 3;
	q = q + 2;
	w = w + q.getValue();
//	cout << 		
}
