#include <iostream>

int &FooCounter()
{
    static int counter = 0;
    return counter;
}

template <typename>
struct FooHelper
{
    inline static int count = []{FooCounter()++; return 0;}();
};

// auto templates requires at least C++17
template <auto> struct Use {};

template <typename T>
void foo(T f)
{
    Use<&FooHelper<T>::count>{};
}
 
struct Bar {
  void operator()(bool x) {}
};

void f1(bool x) {}
 
void f2(bool x) {}

using Foo = decltype(foo<double>); // <-- an explicit template instance

int main() {
  std::cout << "Counted " << FooCounter() << " distinct template instances of foo().\n";
  foo(f1);
  foo(Bar());
  foo(f2);
  foo([](bool x){});
  foo([](bool x){});
}