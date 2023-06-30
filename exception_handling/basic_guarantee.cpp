#include <iostream>
#include "Date.hpp"

int main(int argc, char **argv)
{
    Date d;
    std::cout << d;
    Date second(d);
    std::cout << second;

    Date now = Date::now();
    std::cout << now;
}