main: DummyProduct.o ASubject.o Shop.o main.o
	g++ -o main DummyProduct.o ASubject.o Shop.o main.o && ./main
DummyProduct.o: DummyProduct.cpp DummyProduct.h
	g++ -c DummyProduct.cpp DummyProduct.h 
ASubject.o: ASubject.cpp ASubject.h
	g++ -c ASubject.cpp ASubject.h
Shop.o: Shop.cpp Shop.h IObserver.h
	g++ -c Shop.cpp Shop.h IObserver.h
main.o: main.cpp
	g++ -c main.cpp
clean:
	rm -f main.o ASubject.o DummyProduct.o Shop.o main.o canonical_observer.out *.gch main.exe

