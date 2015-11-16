#include <stdio.h>
#include <stdlib.h>

// http://www.lurklurk.org/linkers/linkers.html

// This is the definition of a uninitialized global variable
int x_global_uninit;

// This is the definition of a initialized global variable
int x_global_init = 1;

// This is the definition of a unitialized global variable, albeit
// one that can only be accessed byname in this C file 
static int y_global_uninit;


// This is the definition of a initialized global variable, albeit
// one that can only be accessed by name in this C file
static int z_global;

// This is a declaration of a function that exists somewhere else 
// in the program (you can ad "extern" beforehand if you like, but it's
// not needed

/*extern*/ int fn_a(int x, int y);

// This is a definition of a function, bu because it is marked as static,
// it can only be referred to by name in this C file alone
static int fn_b(int x)
{
   return x + 1;
}


// This is a definition of a function.
// The function parameter counts as a local variable

int fn_c(int x_local)
{
   // This is the definition of an unitialized local variable;
   int y_local_uninit;
   int y_local_init = 3;

   x_global_uninit = fn_a(x_local, x_global_init);
   y_local_uninit = fn_a(x_local, y_local_init);
   y_local_uninit += fn_b(z_global);
   return (y_global_uninit + y_local_uninit);
}

