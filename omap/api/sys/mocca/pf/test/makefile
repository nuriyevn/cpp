INC_ABS=-ID:/gitrepos/nuriyevn/cppexamples/omap
INC_REL=-I../../../../../


all: main_abs main_rel
main_abs: TestBasicMath.cpp
	g++ TestBasicMath.cpp $(INC_ABS) -o main_abs
main_rel: TestBasicMath.cpp
	g++ TestBasicMath.cpp $(INC_REL) -o main_rel	
clean:
	rm -f *.o *.obj *.exe *.out
