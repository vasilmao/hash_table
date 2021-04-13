OBJ_DIR = obj

hf_test.out: $(OBJ_DIR)/hf_test.o $(OBJ_DIR)/hash_table.o $(OBJ_DIR)/list.o $(OBJ_DIR)/dictionary.o $(OBJ_DIR)/translation.o $(OBJ_DIR)/file_reader.o $(OBJ_DIR)/hash_functions.o
	g++ $(OBJ_DIR)/hf_test.o $(OBJ_DIR)/hash_table.o $(OBJ_DIR)/list.o $(OBJ_DIR)/translation.o $(OBJ_DIR)/dictionary.o $(OBJ_DIR)/file_reader.o $(OBJ_DIR)/hash_functions.o -o hf_test.out

graph: make_graphic.py
	python3 make_graphic.py

$(OBJ_DIR)/hf_test.o: hf_test.cpp dictionary.h hash_table.h list.h translation.h file_reader.h
	g++ -c hf_test.cpp -o $(OBJ_DIR)/hf_test.o

$(OBJ_DIR)/translation.o: translation.cpp translation.h
	g++ -c translation.cpp -o $(OBJ_DIR)/translation.o

$(OBJ_DIR)/hash_table.o: hash_table.cpp hash_table.h list.h translation.h
	g++ -c hash_table.cpp -o $(OBJ_DIR)/hash_table.o

$(OBJ_DIR)/list.o: list.cpp list.h translation.h
	g++ -c list.cpp -o $(OBJ_DIR)/list.o

$(OBJ_DIR)/dictionary.o: dictionary.cpp dictionary.h hash_table.h list.h translation.h file_reader.h
	g++ -c dictionary.cpp -o $(OBJ_DIR)/dictionary.o

$(OBJ_DIR)/file_reader.o: file_reader.cpp file_reader.h
	g++ -c file_reader.cpp -o $(OBJ_DIR)/file_reader.o

$(OBJ_DIR)/hash_functions.o: hash_functions.cpp hash_functions.h translation.h
	g++ -c hash_functions.cpp -o $(OBJ_DIR)/hash_functions.o
