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
