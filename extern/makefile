main: main.cpp several_declaration.cpp test
	g++ main.cpp test.o several_declaration.cpp -o main.exe && ./main.exe
test: test.cpp
	g++ -c test.cpp -o test.o
clean:
	rm -f *.exe *.out *.obj *.o
