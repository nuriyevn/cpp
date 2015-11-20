#include "defined_var.hpp" //if we include this, linker will not complain anymore

extern int var;

int main()
{
   var = 10;
   return 0;
}
