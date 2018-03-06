prog: main.o DHHashTable.o HashTable.o SinglyLinkedList.o Node.o QPHashTable.o
	g++ -g -Wall -std=c++11 main.o DHHashTable.o HashTable.o SinglyLinkedList.o Node.o QPHashTable.o  -o prog

main.o: main.cpp
	g++ -g -Wall -std=c++11 -c main.cpp

DHHashTable.o: DHHashTable.cpp DHHashTable.h
	g++ -g -Wall -std=c++11 -c DHHashTable.cpp

QPHashTable.o: QPHashTable.cpp QPHashTable.h
	g++ -g -Wall -std=c++11 -c QPHashTable.cpp

HashTable.o: HashTable.cpp HashTable.h
	g++ -g -Wall -std=c++11 -c HashTable.cpp

SinglyLinkedList.o: SinglyLinkedList.cpp SinglyLinkedList.h
	g++ -g -Wall -std=c++11 -c SinglyLinkedList.cpp
Node.o: Node.cpp Node.h 
	g++ -g -Wall -std=c++11 -c Node.cpp




clean:
	rm *.o prog
