const_in_class: const_in_class.o main.o
	g++ main.o const_in_class.o -o main
const_in_class.o: const_in_class.cpp
	g++ -c const_in_class.cpp
main.o: main.cpp
	g++ -c main.cpp
template: template.cpp
	g++ template.cpp -o template && ./template
clean:
	rm -f *.exe *.o
