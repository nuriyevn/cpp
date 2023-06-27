// A bunch of CPPUNIT headers
#include "cppunit_headers.hpp"

// Custom libraries
#include "Complex.hpp"
#include "ComplexNumberSuite.hpp"


// Std libraries


int main(int argc, char *argv[])
{
   CppUnit::TextUi::TestRunner runner;
   runner.addTest( ComplexNumberSuite::suite() );

   runner.run();
   return 0;
}

