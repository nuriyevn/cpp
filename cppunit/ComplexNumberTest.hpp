#ifndef __COMPLEX_NUMBER_TEST_HPP__
#define __COMPLEX_NUMBER_TEST_HPP__

#include <iostream>
#include "cppunit_headers.hpp"
#include "Complex.hpp"

using namespace std;

class ComplexNumberTest : public CppUnit::TestCase
{
public:
   ComplexNumberTest(string name);
   void runTest();
};

#endif // __COMPLEX_NUMBER_TEST_HPP__
