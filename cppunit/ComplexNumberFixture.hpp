#ifndef __COMPLEX_NUMBER_FIXTURE__
#define __COMPLEX_NUMBER_FIXTURE__

#include "cppunit_headers.hpp"
#include "Complex.hpp"

class ComplexNumberFixture : public CppUnit::TestFixture
{
private:
   Complex *m_10_1, *m_1_1, *m_11_2, 
            *m_6_undef, *m_6_0, *m_0_6, *m_12_0;
public:
   void setUp();
   void tearDown();
   void testEquality();
   void testAddition();
};

#endif // __COMPLEX_NUMBER_FIXTURE__
