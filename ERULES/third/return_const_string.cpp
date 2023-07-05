#include <iostream>
using namespace std;

// Returning const rvalues is an attempt to prevent such behaviour.
// However, in reality, it does way more harm than good, 
// because now that rvalue references are here, you're just going to prevent move semantics,
//  which sucks, and the above behaviour will probably be prevented by the judicious use of rvalue and lvalue *this overloading. 
// Plus, you'd have to be a bit of a moron to do this anyway.

std::string func() // we can try to add const return here 
{
    return "hai";
}

class I
{
public:
    I(int i)                   : value(i) {}
    void set(int i)            { value = i; }
    // Note that the value returned by operator+ would normally be considered a temporary.
    // But it's clearly being modified. That's not exactly desired.
    // adding const will help to fix the issue
    I operator+(const I& rhs)  { return I(value + rhs.value); }      
    I& operator=(const I& rhs) { value = rhs.value; return *this; }

private:
    int value;
};

class Foo
{
public:
    void bar() {};
};

Foo foo() { return Foo();} ;


int baz() {
   return 3;
}

struct T {};
const T foo4() {
   return T();
}

int main()
{
    func().push_back('c'); // Perfectly valid, yet non-sensical
    I a(2), b(3);
    (a + b) = 2; // another non-senscial, to protect, add const to operator+ return and compiler will spit off an error
    foo().bar(); // non-sense number there, again adding const to return can help.
    // baz() = 4;  // not valid anyway for built-in types, with or without const return type

    foo4() = T();
    return 0;
}

