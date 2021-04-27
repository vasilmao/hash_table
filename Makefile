OBJ_DIR = obj
FLAGS = -O1 -msse4 -mavx -mavx2

speed_test: $(OBJ_DIR)/test_speed.o $(OBJ_DIR)/dictionary.o $(OBJ_DIR)/hash_table.o $(OBJ_DIR)/list.o $(OBJ_DIR)/hash_functions.o $(OBJ_DIR)/translation.o $(OBJ_DIR)/file_reader.o
	g++ $(FLAGS) $(OBJ_DIR)/test_speed.o $(OBJ_DIR)/dictionary.o $(OBJ_DIR)/hash_table.o $(OBJ_DIR)/list.o $(OBJ_DIR)/hash_functions.o $(OBJ_DIR)/translation.o $(OBJ_DIR)/file_reader.o

html: $(OBJ_DIR)/html_translation.o $(OBJ_DIR)/html_translator.o $(OBJ_DIR)/dictionary.o $(OBJ_DIR)/hash_table.o $(OBJ_DIR)/list.o $(OBJ_DIR)/hash_functions.o $(OBJ_DIR)/translation.o $(OBJ_DIR)/file_reader.o
	g++ $(FLAGS) $(OBJ_DIR)/html_translation.o $(OBJ_DIR)/html_translator.o $(OBJ_DIR)/dictionary.o $(OBJ_DIR)/hash_table.o $(OBJ_DIR)/list.o $(OBJ_DIR)/hash_functions.o $(OBJ_DIR)/translation.o $(OBJ_DIR)/file_reader.o -o html_translation.out

hf_test: $(OBJ_DIR)/hf_test.o $(OBJ_DIR)/hash_table.o $(OBJ_DIR)/list.o $(OBJ_DIR)/dictionary.o $(OBJ_DIR)/translation.o $(OBJ_DIR)/file_reader.o $(OBJ_DIR)/hash_functions.o
	g++ $(FLAGS) $(OBJ_DIR)/hf_test.o $(OBJ_DIR)/hash_table.o $(OBJ_DIR)/list.o $(OBJ_DIR)/translation.o $(OBJ_DIR)/dictionary.o $(OBJ_DIR)/file_reader.o $(OBJ_DIR)/hash_functions.o -o hf_test.out

graph: make_graphic.py
	python3 make_graphic.py

$(OBJ_DIR)/test_speed.o: test_speed.cpp dictionary.h hash_table.h list.h file_reader.h translation.h
	g++ $(FLAGS) -c test_speed.cpp -o $(OBJ_DIR)/test_speed.o

$(OBJ_DIR)/html_translation.o: html_translation.cpp html_translator.h dictionary.h hash_table.h list.h file_reader.h translation.h
	g++ $(FLAGS) -c html_translation.cpp -o $(OBJ_DIR)/html_translation.o

$(OBJ_DIR)/html_translator.o: html_translator.cpp html_translator.h dictionary.h hash_table.h list.h file_reader.h translation.h
	g++ $(FLAGS) -c html_translator.cpp -o $(OBJ_DIR)/html_translator.o

$(OBJ_DIR)/hf_test.o: hf_test.cpp dictionary.h hash_table.h list.h translation.h file_reader.h
	g++ $(FLAGS) -c hf_test.cpp -o $(OBJ_DIR)/hf_test.o

$(OBJ_DIR)/translation.o: translation.cpp translation.h
	g++ $(FLAGS) -c translation.cpp -o $(OBJ_DIR)/translation.o

$(OBJ_DIR)/hash_table.o: hash_table.cpp hash_table.h list.h translation.h
	g++ $(FLAGS) -c hash_table.cpp -o $(OBJ_DIR)/hash_table.o

$(OBJ_DIR)/list.o: list.cpp list.h translation.h
	g++ $(FLAGS) -c list.cpp -o $(OBJ_DIR)/list.o

$(OBJ_DIR)/dictionary.o: dictionary.cpp dictionary.h hash_table.h list.h translation.h file_reader.h
	g++ $(FLAGS) -c dictionary.cpp -o $(OBJ_DIR)/dictionary.o

$(OBJ_DIR)/file_reader.o: file_reader.cpp file_reader.h
	g++ $(FLAGS) -c file_reader.cpp -o $(OBJ_DIR)/file_reader.o

$(OBJ_DIR)/hash_functions.o: hash_functions.cpp hash_functions.h translation.h
	g++ $(FLAGS) -c hash_functions.cpp -o $(OBJ_DIR)/hash_functions.o
