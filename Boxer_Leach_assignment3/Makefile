all: Main

run: Main
	./Main input.txt

Main: Main.o BinaryTree.o ItemType.o
	g++ -Wall -g -o Main Main.o BinaryTree.o ItemType.o

Main.o: Main.cpp
	g++ -Wall -std=c++14 -g -O0  -pedantic-errors -c Main.cpp

BinaryTree.o: BinaryTree.cpp BinaryTree.h
	g++ -Wall -std=c++14 -g -O0  -pedantic-errors -c BinaryTree.cpp

ItemType.o: ItemType.cpp ItemType.h
	g++ -Wall -std=c++14 -g -O0  -pedantic-errors -c ItemType.cpp

clean:
	rm -f Main
	rm -f *.o
	rm -f *~