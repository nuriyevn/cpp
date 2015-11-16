// http://cppunit.sourceforge.net/doc/cvs/cppunit_cookbook.html

// Unit-test libraries
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
//#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>

// Custom libraries
#include "Complex.hpp"

// Std libraries
#include <iostream>
#include <cstring>
using namespace std;

//http://cppunit.sourceforge.net/doc/cvs/cppunit_cookbook.html
// Can  accept integer or double

class ComplexNumberTest : public CppUnit::TestCase
{
public:
   ComplexNumberTest(std::string name) 
      : CppUnit::TestCase(name)
   {
      
   }
   void runTest()
   {
      /*Complex<int> first(10, 1);
      cout << "fisrt " << first << endl;
      Complex<int> second(1, 10);
      cout << "second " << second << endl;

      if (first == second)
         cout << "first is equal to second" << endl;
      else
         cout << "second is not equal to second" << endl;

   //   CPPUNIT_ASSERT(Complex<int>(10, 1) == Complex<int>(10, 1));
   
    //  CPPUNIT_ASSERT(!(Complex<int>(1, 1) == Complex<int>(2, 2)));
   */}
};


int main()
{
   /*Complex<int> cint1(4, 7);
   Complex<int> cint2(5, 6);

//   cout << "Cint1 " << cint1 << endl;
  // cout << "Cint2 " << cint2 << endl;
   

   Complex<int> result = cint1.operator+(cint2);
   Complex<int> result2= cint1.operator-(cint2);

   //cout << "result " << result << endl;
   //cout << "result2 " << result << endl;
*/
   ComplexNumberTest cnt("Super test");
   cnt.runTest();
}







