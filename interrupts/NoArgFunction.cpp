#include <iostream>
#include <memory>
#include <cstdio>
using namespace std;

// Function which wrapped with smart pointer
// Smart pointer with call method 
//
class NoArgFunction
{
public:
	class ICallback
	{
	public:
		virtual ~ICallback(){}
		virtual void operator() ()const = 0;
	};

	typedef std::shared_ptr<ICallback> CallbackPtr;

public:
	NoArgFunction()
		: mCallback()
	{

	}
	NoArgFunction(const CallbackPtr callback)
		: mCallback(callback)
	{
			
	}
	NoArgFunction(const NoArgFunction& other)
		:mCallback(other.mCallback)
	{
	}
	NoArgFunction& operator=(const NoArgFunction& other)
	{
		mCallback = other.mCallback;
		return *this;
	}

	// returns true if both object are copy of the same one
	bool operator== (const NoArgFunction& other) const
	{
		return mCallback.get() == other.mCallback.get();
	}

	bool operator != (const NoArgFunction& other) const
	{
		return !(*this == other);
	}

	void clear()
	{
		mCallback = CallbackPtr();
	}

	void call()
	{
		if (mCallback != 0)
		{
			(*mCallback)();
		}
	}

	bool isEmpty() const
	{
		return (mCallback == 0);
	}

private:
	CallbackPtr mCallback;
};


typedef void (*func)();

class SimpleNoArgCallback : public NoArgFunction::ICallback
{
public:
	SimpleNoArgCallback(func f)
		: mFunc(f)
	{
		printf("Address of mFunc = 0x%p\n", &mFunc);
		printf("Value of *mFunc = 0x%p\n", mFunc);
	}
	~SimpleNoArgCallback() {}

	virtual void operator() () const
	{
		cout << "SimpleNoArgCallback::operator()();" << endl;
		(*mFunc)();
		
	}
//	typedef void (*func)(void);
	func mFunc;
};


//typedef void (*NoArgCallbackFunc)();

class ComplexNoArgCallback : public NoArgFunction::ICallback
{
public:
	typedef void (*NoArgCallbackFunc)();

	static NoArgFunction create(NoArgCallbackFunc f)
	{
		return NoArgFunction( 
				NoArgFunction::CallbackPtr(
					new ComplexNoArgCallback(f)));
	}

private:
	ComplexNoArgCallback(NoArgCallbackFunc f)
		: mFunc(f)
	{

	}
public:
	~ComplexNoArgCallback(){}
	virtual void operator()() const
	{
		(*mFunc)();
	}
private:
	NoArgCallbackFunc mFunc;
};

NoArgFunction bind(void (*func)())
{
	return ComplexNoArgCallback::create(func);
}

// typedef shared_ptr<ICallback> mCallback;


void foo (void)
{
	cout << "i'm foo() function" << endl;
}

void bar(void)
{
	cout << "I'm bar() function" << endl;
}


int main()
{
	
/*	std::function<void()> foo_function =  std::bind(foo);

	foo_function();
	NoArgFunction bar_callback;
	if (bar_callback.isEmpty())	
		cout << "bar_callback is empty" << endl;

	bar_callback.call();

	
	printf("Value of foo = 0x%p\n", foo);
	printf("Addres of &foo = 0x%p\n", &foo);

	SimpleNoArgCallback s_foo(foo);
	s_foo();

//	SimpleNoArgCallback empty_cb;
*/
/*	NoArgFunction foo_noargfunction = 
		ComplexNoArgCallback::create(foo);
	
	foo_noargfunction.call();
*/
	NoArgFunction foo_noargfunction = bind(foo);
	foo_noargfunction.call();

	NoArgFunction bar_noargfunction = bind(bar);
	bar_noargfunction.call();
	
//	ComplexNoArgCallback complex_foo(foo);
//	complex_foo();

	return 0;
}


