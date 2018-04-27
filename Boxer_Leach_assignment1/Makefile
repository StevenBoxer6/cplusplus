all: Main

run: Main
	./Main input.txt

Main: Main.o LinkedList.o ItemType.o
	g++ -Wall -g -o Main Main.o LinkedList.o ItemType.o

Main.o: Main.cpp
	g++ -Wall -std=c++14 -g -O0  -pedantic-errors -c Main.cpp

LinkedList.o: LinkedList.cpp LinkedList.h
	g++ -Wall -std=c++14 -g -O0  -pedantic-errors -c LinkedList.cpp

ItemType.o: ItemType.cpp ItemType.h
	g++ -Wall -std=c++14 -g -O0  -pedantic-errors -c ItemType.cpp

clean:
	rm -f Main
	rm -f *.o
	rm -f *~