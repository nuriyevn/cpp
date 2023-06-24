struct A
{
	int x;
	A(int x = 1) : x(x) {}
};

struct B: A
{
	// B::B() is implicitly-defined, calls A::A()
};

struct C
{
	A a;
	// C::C() is implicitly-defined, calls A::A()
};

//struct D: A


int main
{
	A a;
	B b;
	C c;
}
