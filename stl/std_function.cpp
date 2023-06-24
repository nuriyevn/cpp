#include <functional>
#include <iostream>

struct Foo {
	Foo(int num) : num_(num) {}
	void print_add(int i) const
	{
		std::cout << num_ + i << "\n";
	}
	int num_;
};

void print_num(int i)
{
	std::cout << i << '\n';
}

struct PrintNum 
{
	void operator() (int i) const
	{
		std::cout << i << '\n';
	}
};


int main()
{
	// Storing a free function
	std::function<void(int)> f_display = print_num;
	
	// Storing a lambda
	std::function<void()> f_display_42 = [] () { print_num(42); };
	f_display_42();

	// Store the result of a call to std::bind
	std::function<void()> f_display_31337 = std::bind(print_num, 31337);
	f_display_31337();

	// Store a call to a member function
	std::function<void(const Foo&, int)> f_add_display = &Foo::print_add;
	const Foo foo(314159);
	f_add_display(foo, 1);


}
