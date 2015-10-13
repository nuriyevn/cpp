#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

template<class ptr_type>
class shared_pointer
{
public:
	shared_pointer(ptr_type* ptr);
	~shared_pointer();
	ptr_type* get();
	ptr_type* operator->();
	ptr_type& operator*();
private:
	ptr_type* actual_ptr;

};


template<class ptr_type>
shared_pointer<ptr_type>::shared_pointer(ptr_type* ptr)
	: actual_ptr(ptr)
{
	cout << "Constructor of shared_pointer, addr: " 
		<< hex << ptr << endl;
}

template<class ptr_type>
shared_pointer<ptr_type>::~shared_pointer()
{
	cout << "Shared pointer destructor is called for pointer:"
		<< hex << actual_ptr << endl;
	delete actual_ptr;
}

template<class ptr_type>
ptr_type* shared_pointer<ptr_type>::get()
{
	return actual_ptr;
}

template<class ptr_type>
ptr_type* shared_pointer<ptr_type>::operator->()
{
	return actual_ptr;
}

template<class ptr_type>
ptr_type& shared_pointer<ptr_type>::operator*()
{
	return *actual_ptr;
}


int main()
{
	int *a = new int(17);
	double *d = new double(3.14);
	
	cout << "int pointer addr: " << hex << a << endl;
	cout << "double pointr addr: " << hex << d << endl;

//	char *msg = new char[200]("message");

	cout << *a << endl;
	cout << *d << endl;;

	shared_pointer<int> spi(a);
	shared_pointer<double> spd(d);

//	shared_pointer<char*> spc(msg);
	cout << "spi.get() = " << hex << spi.get() << endl;
	cout << "spd.get() = " << hex << spd.get() << endl;

}
