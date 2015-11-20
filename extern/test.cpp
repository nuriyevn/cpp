#include <iostream>
using namespace std;


int testSum(int a, int b)
{
   extern int sum(int a, int b); // third declaration of the sum function

   int ethalon = a + b;

   if (sum(a, b) == ethalon)
      cout << "test is passed" << endl;
}
