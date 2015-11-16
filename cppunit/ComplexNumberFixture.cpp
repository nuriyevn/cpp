#include "ComplexNumberFixture.hpp"

#ifndef RELEASE
#include <iostream>
using namespace std;
#endif

void ComplexNumberFixture::setUp()
{
   m_10_1 = new Complex(10, 1);
   m_1_1 = new Complex(1, 1);
   m_11_2 = new Complex(11, 2);
   m_6_undef = new Complex(6);
   m_6_0 = new Complex(6, 0);
   m_0_6 = new Complex(0, 6);
   m_12_0 = new Complex(12, 0);
}

void ComplexNumberFixture::tearDown()
{
   delete m_10_1;
   delete m_1_1;
   delete m_11_2;
   delete m_6_undef;  
   delete m_6_0;
   delete m_0_6;
   delete m_12_0;
}

void ComplexNumberFixture::testEquality()
{
// INTENTIONALLY WRITTEN WRONG TEST
#ifndef RELEASE
   cout << "ComplexNumberFixture::testEquality()" << endl;
   cout << *m_10_1 << endl;
   cout << *m_11_2 << endl;
   CPPUNIT_ASSERT(false);
   CPPUNIT_ASSERT(*m_10_1 == *m_11_2);
#endif
//
   CPPUNIT_ASSERT(*m_10_1 == *m_10_1);
   CPPUNIT_ASSERT(!(*m_10_1 == *m_11_2));
   CPPUNIT_ASSERT(*m_6_undef == *m_6_0);
   CPPUNIT_ASSERT(!(*m_6_undef == *m_0_6));
}

void ComplexNumberFixture::testAddition()
{
   CPPUNIT_ASSERT(*m_10_1 + *m_1_1 == *m_11_2);  
   CPPUNIT_ASSERT(*m_6_0 + *m_6_0 == *m_12_0);
   // checking whether m_6_0 object has not been modified during operator+ call
   CPPUNIT_ASSERT(*m_6_0 + *m_6_0 == *m_12_0);
   CPPUNIT_ASSERT(*m_12_0 == *m_6_0 + *m_6_0);
}


