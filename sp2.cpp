#include <iostream>
#include <memory>
#include <cstdio>
using namespace std;
struct C 
{
	int *data;
};

class ICallback
{
public:
	virtual ~ICallback() {}
	virtual void operator()() const = 0;
};



class NoArgCallback : public ICallback
{
public:

	typedef void (*NoArgCallbackFunc)();

	NoArgCallback(NoArgCallbackFunc f)
		: mFunc(f)
	{
	}

	virtual void operator()() const
	{
		(*mFunc)();
	}
private:
	NoArgCallbackFunc mFunc;
};

void baz()
{
	cout << "I'm baz() function" << endl;
}


int main()
{
	std::shared_ptr<int>	p1;
	std::shared_ptr<int>	p2(nullptr);
	std::shared_ptr<int>	p3(new int);
	

	std::shared_ptr<ICallback> CallbackPtr;

//	printf("Value of CallbackPtr = 0x%p\n", CallbackPtr);
	printf("Address of &CallbackPtr = 0x%p\n", &CallbackPtr);
	printf("Dereferene of *CallbackPtr = 0x%p\n", CallbackPtr.get());
	
//	NoArgCallback my_cb = (NoArgCallback)baz;


	printf("Address of &CallbackPtr2 = 0x%p\n", &CallbackPtr2);
	printf("Dereference of CallbackPtr2 = 0x%p\n", CallbackPtr2.get());
		
	//(*CallbackPtr)();
}
