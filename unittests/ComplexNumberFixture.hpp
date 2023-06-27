#ifndef __COMPLEX_NUMBER_FIXTURE__
#define __COMPLEX_NUMBER_FIXTURE__

#include "cppunit_headers.hpp"
#include "Complex.hpp"

class ComplexNumberFixture : public CppUnit::TestFixture
{
   CPPUNIT_TEST_SUITE(ComplexNumberFixture);
   CPPUNIT_TEST(testEquality);
   CPPUNIT_TEST(testAddition);
   CPPUNIT_TEST_SUITE_END();

private:
   Complex *m_10_1, *m_1_1, *m_11_2, 
            *m_6_undef, *m_6_0, *m_0_6, *m_12_0;
public:
   void setUp();
   void tearDown();
   void testEquality();
   void testAddition();
};

CPPUNIT_TEST_SUITE_REGISTRATION(ComplexNumberFixture);

#endif // __COMPLEX_NUMBER_FIXTURE__
