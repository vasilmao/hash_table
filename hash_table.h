#ifndef HashTableFile
#define HashTableFile

#include "list.h"

typedef size_t key_type

struct HashTable {
    size_t length;
    List* array;
    key_type (*hash_function)(value_type value);
};

bool HT_search(HashTable* table, value_type find_value);

#endif
