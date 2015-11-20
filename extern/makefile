main: main.cpp several_declaration.cpp test
	g++ main.cpp test.o several_declaration.cpp -o main.exe && ./main.exe
test: test.cpp
	g++ -c test.cpp -o test.o
extern_var: header.hpp source1.cpp source2.cpp
	g++ header.hpp source1.cpp source2.cpp -o extern_var.exe && ./extern_var.exe
undefined_var: undefined_var.cpp  defined_var.hpp
	g++ defined_var.hpp undefined_var.cpp -o undefined_var.exe && ./undefined_var.exe
defined_var: defined_var.hpp
	g++ -c defined_var.hpp -o defined_var.o
init_extern: init_extern.cpp
	g++ init_extern.cpp -o init_extern.exe && ./init_extern.exe
clean:
	rm -f *.exe *.out *.obj *.o
