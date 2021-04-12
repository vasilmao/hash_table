dict.out: main.o hash_table.o list.o dictionary.o translation.o file_reader.o hash_functions.o
	g++ main.o hash_table.o list.o translation.o dictionary.o file_reader.o hash_functions.o -o dict.out

graph: make_graphic.py
	python3 make_graphic.py

main.o: main.cpp dictionary.h hash_table.h list.h translation.h file_reader.h
	g++ -c main.cpp

translation.o: translation.cpp translation.h
	g++ -c translation.cpp

hash_table.o: hash_table.cpp hash_table.h list.h translation.h
	g++ -c hash_table.cpp

list.o: list.cpp list.h translation.h
	g++ -c list.cpp

dictionary.o: dictionary.cpp dictionary.h hash_table.h list.h translation.h file_reader.h
	g++ -c dictionary.cpp

file_reader.o: file_reader.cpp file_reader.h
	g++ -c file_reader.cpp

hash_functions.o: hash_functions.cpp hash_functions.h translation.h
	g++ -c hash_functions.cpp
