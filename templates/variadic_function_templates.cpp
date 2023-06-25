// https://iamsorush.com/posts/cpp-variadic-template/
#include <iostream>

struct FooCounter 
{
    static unsigned n;
    FooCounter(){++n;}
};

unsigned FooCounter::n = 0;

// there is no for-loop style code to iterate the parameters of a pack.
template<typename ...T>
auto sum(const T&... args) {
    std::cout<< "Number or arguments sent: " <<  sizeof...(args);
}

auto f(auto... args){
    static FooCounter count;
    return (args+...);
    // turns to (arg1+ arg2 + arg3 + ...)
}

auto norm(auto... args)
{
    return sqrt(((args*args)+...));
}

auto root(const auto& x)
{
    return sqrt(x);
}

auto h(const auto&... args)
{
    return ( root(args) + ...);
}


int main()
{
    //sum<int>(5, 7, -3, 45);
    // 0110 0110 0110 0101
    //  66         65
    //std::cout << "\n" << f(5, 7, -3, 45);
    std::cout << f(1);
    std::cout << f(1, 2);
    std::cout << f(1, 2, 3);
    std::cout << f(1, 2, 4);
    std::cout << std::endl << norm(1, 2, 4);
    std::cout << std::endl << h(1, 4);

    std::cout << "Number of distinct instances: " << FooCounter::n << std::endl;
}