complex: Complex.hpp Complex.cpp
	g++ -Wfatal-errors -c Complex.cpp -o ./complex.o
complexmain: ComplexNumberTest.cpp
	g++ -Wfatal-errors ComplexNumberTest.cpp -o complexmain.out -LC:/cygwin64/lib -lcppunit -IC:/cygwin64/usr/include
cppunit: basicmath.o testbasicmath.o
	g++ -Wfatal-errors basicmath.o testbasicmath.o -o cppunit  -lcppunit -IC:/cygwin64/usr/include
basicmath.o: CBasicMath.cpp CBasicMath.hpp
	g++ -c  CBasicMath.cpp -o basicmath.o
testbasicmath.o: TestBasicMath.cpp
	g++ -c TestBasicMath.cpp -o testbasicmath.o
clean:
	rm -f *.o *.obj *.exe *.out
