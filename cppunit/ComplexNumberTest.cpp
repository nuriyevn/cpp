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
#include <netinet/in.h>

class Complex {
public:  
   Complex(int r, int i)
      : real(r), im(i)
   {
     
   }
   ~Complex(){}
   Complex(const Complex& right)
   {
      this->real = right.real;
      this->im = right.im;
   }

private:
   int real;
   int im;
};


class ComplexNumberTest : public CppUnit::TestCase
{
public:
   ComplextNumberTest(std::string name) : CppUnit::TestCase(name)
   {
      
   }
   void runTest()
   {
      CPPUNIT_ASSERT(Complex(10, 1) == Complex(10, 1));
      CPPUNIT_ASSERT(!Complex(1, 1) == Complex(2, 2);
   }
};





