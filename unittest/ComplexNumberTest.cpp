#include "ComplexNumberTest.hpp"

ComplexNumberTest::ComplexNumberTest(string name)
   : CppUnit::TestCase(name)
{  
}

void ComplexNumberTest::runTest()
{
#ifndef RELEASE
   CPPUNIT_ASSERT(Complex(10, 1) == Complex(1, 10));
#endif   
   CPPUNIT_ASSERT(Complex(10, 1) == Complex(10, 1));
   CPPUNIT_ASSERT(!(Complex(1, 1) == Complex(2, 2)));
   CPPUNIT_ASSERT(Complex(10) == Complex(10, 0));
   CPPUNIT_ASSERT(!(Complex(10) == Complex(0, 10)));
}
