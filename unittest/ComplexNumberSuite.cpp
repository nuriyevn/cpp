#include "ComplexNumberSuite.hpp"

CppUnit::Test *ComplexNumberSuite::suite()
{
   CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("ComplexNumberFixture");

   suiteOfTests->addTest(new CppUnit::TestCaller<ComplexNumberFixture>("testEquality", &ComplexNumberFixture::testEquality));
   suiteOfTests->addTest(new CppUnit::TestCaller<ComplexNumberFixture>("testAddition", &ComplexNumberFixture::testAddition));

   return suiteOfTests;
}
