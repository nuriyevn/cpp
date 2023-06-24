#include <iostream>
#define POINTER_DEBUG


class manager
{
public:
	manager() : shared_count(0), weak_count(0)
	{
	}

private:
	int	shared_count;
	int weak_count;
	void *actual_ptr;
};

template<class ptr_type>
class unique_pointer
{
public:
	unique_pointer(ptr_type* ptr)
		: actual_ptr(ptr)
	{	
	}
	~unique_pointer();

	{
#ifdef POINTER_DEBUG
		cout << "Shared pointer destructor is called for pointer: " << 
#endif
	}
};

template<class ptr_type>
unique_pointer<ptr_type>::unique_pointer()

{
}


class Base
{
public:
	Base::Base() {}
	Base::~Base() {}
}	;


int main()
{
	Base *b = new Base;

	shared_pointer<Base> sp1(b);

}
