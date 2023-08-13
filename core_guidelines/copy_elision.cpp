// In C++ computer programming, copy elision refers to a compiler optimization technique 
// that eliminates unnecessary copying of objects. 
// https://stackoverflow.com/questions/12953127/what-are-copy-elision-and-return-value-optimization

#include <iostream>
using namespace std;

/*

11.9.6 Copy/move elision
[class.copy.elision]

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

int n = 0;

struct C {
    C() {}
    explicit C(int) { cout << "exclicit ctor\n";  };
    C(const C& ) { cout << "copy constr\n"; ++n; } // the copy constructor has  a visible side effect
    // it modifies an object with static storage duration
};

C foo()
{
    return C();
}


class ABC {
    public:   
        const char *a;  
        ABC()  
        { cout<<"def Constructor"<<endl; }  
        ABC(const char *ptr)  
        { cout<<"copy Constructor"<<endl; }  
        ABC(ABC  &obj)  
        { cout<<"copy constructor"<<endl;}  
        ABC(ABC&& obj)  
        { cout<<"Move constructor"<<endl; }  
        ~ABC()  
        { cout<<"Destructor"<<endl; }  
};


ABC fun123()  
{ 
    ABC obj; return obj; 
}  

ABC xyz123()  
{  
    return ABC(); 
}  

int main()
{
    C c1(42); // direct initialization, calls C::C(int)
    C c2 = C(42); // copy initialization, can call C::C(const C&)

    cout << n << endl; // prints 0 if the copy was elided, 1 otherwise;
    /*
    Copy elision is a compiler optimization technique that eliminates unnecessary copying/moving of objects.
    In the following circumstances, a compiler is allowed to omit copy/move operations 
    and hence not to call the associated constructor:

    NRVO (Named Return Value Optimization): If a function returns a class type by value 
    and the return statement's expression is the name of a non-volatile object with automatic storage duration
    (which isn't a function parameter), then the copy/move that would be performed by a non-optimising compiler can be omitted. 
    If so, the returned value is constructed directly in the storage to which the function's return value would 
    otherwise be moved or copied.

    RVO (Return Value Optimization): If the function returns a nameless temporary object 
    that would be moved or copied into the destination by a naive compiler,
    the copy or move can be omitted as per 1.
    */

    ABC abc;
    ABC obj1(fun123());    //NRVO 
    ABC obj2(xyz123());    //RVO, not NRVO 
    ABC xyz = "Stack Overflow";//RVO  ???
}