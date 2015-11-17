#include <iostream>

#include "Complex.hpp"
#include "cppunit_headers.hpp"
using namespace std;

class ComplexNumberTest : public CppUnit::TestFixture
{
private:
   Complex *m_10_1, *m_1_1, *m_11_2;

public:
   void setUp()
   {
      m_10_1 = new Complex(10, 1);
      m_1_1 = new Complex(1, 1);
      m_11_2 = new Complex(11, 2);
   }
   void tearDown()
   {
      delete m_10_1;
      delete m_1_1;
      delete m_11_2;
   }
   void testEquality()
   {
      CPPUNIT_ASSERT(*m_10_1 == *m_10_1);
      CPPUNIT_ASSERT(!(*m_10_1 == *m_11_2));
   }   
   void testAddition()  
   {
      CPPUNIT_ASSERT(*m_10_1 + *m_1_1 == *m_11_2);
   }
   void testSubtraction()
   {  
      CPPUNIT_ASSERT(*m_11_2 - *m_1_1 == *m_10_1);
      CPPUNIT_ASSERT(!(*m_1_1 - *m_11_2 == *m_10_1));
   }
   void testMultiplication()
   {
      CPPUNIT_ASSERT(*m_11_2 * *m_1_1 == Complex(9, 13));      
      CPPUNIT_ASSERT(*m_10_1 * *m_1_1 == Complex(9, 11));
   }
   void testDivision()
   {  
      CPPUNIT_ASSERT(Complex(7, -4) / Complex(3, 2) == Complex(1, -2));
      //CPPUNIT_ASSERT((*m_11_2 / *m_1_1) == Complex(6.5, -4.5));

      Complex ethalon(0.108, 0.089);

     Complex r; //= *m_1_1 / *m_10_1;
     
      cout << "Ethalon = " << ethalon << endl;
      cout << "r = " << r << endl; 

      cout << "isFloatEqual(r.real, ethalon.real) = " << Complex::isFloatEqual(r.getReal(), ethalon.getReal()) << endl;
      cout << "isFloatEqual(r.im , ethalon.im) = " << Complex::isFloatEqual(r.getImag(), ethalon.getImag()) << endl; 

      if (Complex::isFloatEqual(r.getReal(), ethalon.getReal()) &&
         Complex::isFloatEqual(r.getImag(), ethalon.getImag()))
      {
         cout << "two complex values are equal" << endl;
      }
      else
         cout << "two complex value are NOT equal" << endl;
       
      Complex temp = *m_1_1 / *m_10_1;
      CPPUNIT_ASSERT(ethalon == temp);  
      CPPUNIT_ASSERT(r == ethalon);
   }
   
   static CppUnit::Test *suite()
   {
      CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("ComplexNumberTest");
      suiteOfTests->addTest(new CppUnit::TestCaller<ComplexNumberTest>("testEquality", &ComplexNumberTest::testEquality));
      suiteOfTests->addTest(new CppUnit::TestCaller<ComplexNumberTest>("testAddition", &ComplexNumberTest::testAddition));
      suiteOfTests->addTest(new CppUnit::TestCaller<ComplexNumberTest>("testMultiplication", &ComplexNumberTest::testMultiplication));
      suiteOfTests->addTest(new CppUnit::TestCaller<ComplexNumberTest>("testDivision", &ComplexNumberTest::testDivision));
      return suiteOfTests; 
   }  
};

int main()
{
/*   CppUnit::TestCaller<ComplexNumberTest> test("testEquality", &ComplexNumberTest::testEquality);
   CppUnit::TestResult result;
   test.run(&result);
*/
   CppUnit::TextUi::TestRunner runner;
   runner.addTest(ComplexNumberTest::suite());
   runner.run(); 
 
/*   CppUnit::TestSuite suite;
   CppUnit::TestResult result;
   suite.addTest(new CppUnit::TestCaller<ComplexNumberTest>("testEquality", &ComplexNumberTest::testEquality));

   suite.addTest(new CppUnit::TestCaller<ComplexNumberTest>("testAddition", &ComplexNumberTest::testAddition));

 */
}  

