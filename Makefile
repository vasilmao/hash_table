dict.out: main.o hash_table.o list.o dictionary.o translation.o
	g++ main.o hash_table.o list.o translation.o dictionary.o -o dict.out

main.o: main.cpp
	g++ -c main.cpp

translation.o: translation.cpp translation.h
	g++ -c translation.cpp

hash_table.o: hash_table.cpp hash_table.h list.h translation.h
	g++ -c hash_table.cpp

list.o: list.cpp list.h translation.h
	g++ -c list.cpp

dictionary.o: dictionary.cpp dictionary.h hash_table.h list.h translation.h
	g++ -c dictionary.cpp
