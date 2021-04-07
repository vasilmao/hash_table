dict.out: main.o hash_table.o list.o
	g++ main.o hash_table.o list.o -o dict.out

main.o: main.cpp
	g++ -c main.cpp

hash_table.o: hash_table.cpp
	g++ -c hash_table.cpp

list.o: list.cpp
	g++ -c list.cpp
