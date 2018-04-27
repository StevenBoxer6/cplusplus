all: main

main: main.o SortingMethods.o
	g++ -Wall -g -o main main.o SortingMethods.o

main.o: main.cpp
	g++ -Wall -std=c++14 -g -O0  -pedantic-errors -c main.cpp

SortingMethods.o: SortingMethods.cpp SortingMethods.h
	g++ -Wall -std=c++14 -g -O0  -pedantic-errors -c SortingMethods.cpp

clean:
	rm -f Main
	rm -f *.o
	rm -f *~