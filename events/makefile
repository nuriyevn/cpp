events: main.o EventDispatcher.o
	g++ -o events main.o EventDispatcher.o
main.o: main.cpp
	g++ -c main.cpp
EventDispatcher.o: EventDispatcher.cpp
	g++ -c EventDispatcher.cpp
clean:
	rm -f events *.o
	
