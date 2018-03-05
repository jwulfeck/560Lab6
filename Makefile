prog: main.o DHHashTable.o QPHashTable.o
	g++ -g -Wall -std=c++11 main.o DHHashTable.o QPHashTable.o -o prog

main.o: main.cpp
	g++ -g -Wall -std=c++11 -c main.cpp

DHHashTable.o: DHHashTable.cpp DHHashTable.h
	g++ -g -Wall -std=c++11 -c DHHashTable.cpp

QPHashTable.o: QPHashTable.cpp QPHashTable.h
		g++ -g -Wall -std=c++11 -c QPHashTable.cpp

clean:
	rm *.o prog
