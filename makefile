all: main

main: test.o similarity.o HashFactory.o Manual.o Reader.o
	g++ test.o similarity.o HashFactory.o Manual.o Reader.o -o main -std=c++11
test.o: test.cpp
	g++ -c test.cpp -o test.o -std=c++11
similarity.o: similarity.cpp
	g++ -c similarity.cpp -o similarity.o -std=c++11
HashFactory.o: HashFactory.cpp
	g++ -c HashFactory.cpp -o HashFactory.o -std=c++11
Manual.o: Manual.cpp
	g++ -c Manual.cpp -o Manual.o -std=c++11
Reader.o: Reader.cpp
	g++ -c Reader.cpp -o Reader.o -std=c++11

clean:
	del *.o
