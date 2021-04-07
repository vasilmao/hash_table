#ifndef HashTableFile
#define HashTableFile

#include "list.h"


const size_t HT_TABLE_SIZE = 4079;
typedef size_t key_type;

struct HashTable {
    size_t length;
    List** array;
    key_type (*hash_function)(value_type value);
};

HashTable* HT_Create(key_type (*hash_function)(value_type value));
void HT_Destroy(HashTable* table);
bool HT_search(HashTable* table, value_type find_value);
void HT_add(HashTable* table, value_type add_value);

#endif
