#include "LibraryCode.hpp"

#include <math.h>
#include <stdexcept>
#include <iostream>

double mySqrt(double input)
{
    if (input < 0)
    {
        std::cout << "Exception thrown\n";
        throw std::logic_error("Negative argument!");
    }
    std::cout << "No exception thrown\n";
    return sqrt(input);
}

int numberOfDaysLived(int age)
{
    if (age < 0)
    {
        std::cout << "Exception thrown\n";
        throw std::runtime_error("Age couldn't be negative");
    }
    else if (age > 120)
    {
        std::cout << "Exception thrown\n";
        throw std::logic_error("This is unreal");
    }

    std::cout << "No exception thrown\n";
    return age * 365;
}