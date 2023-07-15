// In C++ computer programming, copy elision refers to a compiler optimization technique 
// that eliminates unnecessary copying of objects. 
#include <iostream>
using namespace std;

int n = 0;

/*
The C++ language standard generally allows implementations to perform any optimization, 
provided the resulting program's observable behavior is the same as if, i.e. pretending, 
the program were executed exactly as mandated by the standard. Beyond that, 
the standard also describes a few situations where copying can be eliminated even 
if this would alter the program's behavior, the most common being the return value optimization (see below). 
Another widely implemented optimization, described in the C++ standard, 
is when a temporary object of class type is copied to an object of the same type.[1] 
As a result, copy-initialization is usually equivalent to direct-initialization in terms of performance, 
but not in semantics; copy-initialization still requires an accessible copy constructor.[2] 
The optimization can not be applied to a temporary object that has been bound to a reference.
*/

struct C {
    explicit C(int) { cout << "exclicit ctor\n";  };
    C(const C& ) { cout << "copy constr\n"; ++n; } // the copy constructor has  a visible side effect
    // it modifies an object with static storage duration
};


int main()
{
    C c1(42); // direct initialization, calls C::C(int)
    C c2 = C(42); // copy initialization, can call C::C(const C&)
    
    cout << n << endl; // prints 0 if the copy was elided, 1 otherwise;
}