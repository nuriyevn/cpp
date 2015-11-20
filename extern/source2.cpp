#include <iostream>
#include "header.hpp"

// int global_x = 6; // this will produce multiple definition error

void print_global_x()
{
   std::cout << global_x << std::endl;
}
