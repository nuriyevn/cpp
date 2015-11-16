// http://cppunit.sourceforge.net/doc/cvs/cppunit_cookbook.html

// A bunch of required CPPUNIT headers
#include "cppunit_headers.hpp"

// Custom libraries
#include "Complex.hpp"
#include "ComplexNumberTest.hpp"
#include "ComplexNumberFixture.hpp"

// Std libraries
#include <iostream>
#include <cstring>
using namespace std;



int main()
{
   // Using TestCase
   ComplexNumberTest cnt("Super test");
   cnt.runTest();


   // Using TestFixture

   CppUnit::TestCaller<ComplexNumberFixture>  testForEquality("testEquality", &ComplexNumberFixture::testEquality);

   CppUnit::TestResult resultOfEquality;
   testForEquality.run(&resultOfEquality);

   CppUnit::TestCaller<ComplexNumberFixture> testForAddition("testAddition", &ComplexNumberFixture::testAddition);
   CppUnit::TestResult resultOfAddition;

   testForAddition.run(&resultOfAddition);

   // Using TestSuite   
   CppUnit::TestSuite math_suite;
// CppUnit::Test *pointer = &math_suite;
   math_suite.addTest(new CppUnit::TestCaller<ComplexNumberFixture> ("testAddition", &ComplexNumberFixture::testAddition));

   CppUnit::TestSuite suite;
   CppUnit::TestResult suite_result;
   
   suite.addTest(new CppUnit::TestCaller<ComplexNumberFixture> ("testEquality", &ComplexNumberFixture::testEquality));

   suite.addTest(new CppUnit::TestCaller<ComplexNumberFixture> ("testAddition", &ComplexNumberFixture::testAddition));

   // suite.addTest(&math_suite);

   suite.run(&suite_result);

   // Using suite method
   

   Complex c(7);
   cout << c << endl;
}





