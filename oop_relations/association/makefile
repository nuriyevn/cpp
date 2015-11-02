old_association: association.cpp
	g++ association.cpp -o association && ./association
association: association.cpp Manager.o SwipeCard.o
	g++ association.cpp Manager.o SwipeCard.o -o association.exe && ./association.exe
manager: Manager.cpp
	g++ -c Manager.cpp
swipecard: SwipeCard.cpp
	g++ -c SwipeCard.cpp
#association_main: association.cpp
#	g++ -c assi

clean:
	rm -f *.exe *.o
