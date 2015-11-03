cppunit: basicmath.o testbasicmath.o
	g++ -Wfatal-errors basicmath.o testbasicmath.o -o cppunit && ./cppunit

basicmath.o: CBasicMath.cpp CBasicMath.hpp
	g++ -c  CBasicMath.cpp -o basicmath.o
testbasicmath.o: TestBasicMath.cpp
	g++ -c TestBasicMath.cpp
clean:
	rm -f *.o *.obj *.exe *.out
