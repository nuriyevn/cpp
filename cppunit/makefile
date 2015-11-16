complexclass: Complex.hpp Complex.cpp
	g++ -Wfatal-errors -c Complex.cpp -o ./complexclass.o
complexmain: main.cpp complexclass complextestcase complexfixture
	g++ -Wfatal-errors main.cpp complexclass.o complextestcase.o complexfixture.o -o complexmain.out -lcppunit && ./complexmain.out
complextestcase: ComplexNumberTest.cpp complexclass
	g++ -DRELEASE -c ComplexNumberTest.cpp -lcppunit -o complextestcase.o
complexfixture: ComplexNumberFixture.cpp ComplexNumberFixture.hpp complexclass
	g++ -c ComplexNumberFixture.cpp -lcppunit -o complexfixture.o 
complexsuite: ComplexNumberSuite.cpp complexclass complexfixture
	g++ -c ComplexNumberSuite.cpp -lcppunit -o complexsuite.o
cppunit: basicmath.o testbasicmath.o
	g++ -Wfatal-errors basicmath.o testbasicmath.o -o cppunit  -lcppunit -IC:/cygwin64/usr/include
basicmath.o: CBasicMath.cpp CBasicMath.hpp
	g++ -c  CBasicMath.cpp -o basicmath.o
testbasicmath.o: TestBasicMath.cpp
	g++ -c TestBasicMath.cpp -o testbasicmath.o
clean:
	rm -f *.o *.obj *.exe *.out
