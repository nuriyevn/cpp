// https://stackoverflow.com/questions/63698324/how-to-check-the-count-of-function-template-instantiations
#include <iostream>

struct FooCounter {
    static unsigned n;
    FooCounter() { ++n; }
};
struct TotalFooCounter {
    static unsigned n;
    TotalFooCounter() { ++n; }
};

unsigned  FooCounter::n = 0;
unsigned  TotalFooCounter::n = 0;

// function is passed as a template argument for a template function is perfectly valid
template <typename T>
void foo(T f)
{
    // static here is very important otherwise we will not be able to count the true number of instantiated templates
    static FooCounter count;
    // rather just a total usage number
    TotalFooCounter totalCount;
}

// Looks like any structure with overloaded () operator are unique, 
// even if they have the same return values and arguments as a regular function not enclosed in a structure
struct Bar {
    void operator()(bool x) {}
};

struct Bar2 {
    void operator()(bool x) {}
};

// Those will use the same template instance
void f1(bool x) {}
void f2(bool x) {}

int main() 
{

    foo(f1); // f1 and f2 have the same signature thus they have they the same template instance
    foo(Bar());
    foo(Bar2());
    foo(f2);

    // The duplicated call of foo([](bool x){}); is the one where each counts.
    // The reason is that each lambda gets a unique type (generated internally by the compiler). 
    // (That they are literally identical is regardless.) Hence, template foo() is instanced for each of them.
    foo([](bool x){}); // despite the same signature those lambdas have a different types
    foo([](bool x){});
    foo([](bool x){});
    std::cout << "Counted " << FooCounter::n << " distinct template instances of foo().\n";
    std::cout << "Overal counted " << TotalFooCounter::n << " distinct template instances of foo().\n";

    return 0;
}