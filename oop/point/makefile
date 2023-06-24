CXX = g++
CXXFLAGS = -Wall -g

main: main.o Point.o Rectangle.o
	$(CXX) $(CXXFLAGS) -o main main.o Point.o Rectangle.o

main.o: main.cpp Point.h Rectangle.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Point.o: Point.h

Rectangle.o: Rectangle.h Point.h;
