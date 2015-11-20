/*
1. Declaration can be done any number of times but definition only once.
2. “extern” keyword is used to extend the visibility of variables/functions().
3. Since functions are visible through out the program by default. The use of extern is not needed in function declaration/definition. Its use is redundant.
4. When extern is used with a variable, it’s only declared not defined.
5. As an exception, when an extern variable is declared with initialization, it is taken as definition of the variable as well.
*/


#include <iostream>

using namespace std;


void f()
{
   extern int sum(int a, int b); // first declaration of function
   int first = -14, second = -345;

   cout << "From f() function: " <<  sum(first, second) << endl;

}

int main()
{

   extern int sum(int a, int b); // second declation of function
   extern int testSum(int a, int b);
   int x = 5, y = 6;

   cout << sum(x, y) << endl;
   testSum(16, 26);
   f();
   
}
