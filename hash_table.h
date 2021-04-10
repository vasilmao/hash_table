#ifndef HASH_TABLE_File
#define HASH_TABLE_File

#include "list.h"


const size_t HT_TABLE_SIZE = 4079;
typedef size_t key_type;

struct HashTable {
    size_t   length;
    List**   array;
    key_type (*hash_function)    (value_type value);
    bool     (*equality_function)(value_type val1, value_type val2);
};

HashTable* HT_Create(key_type (*hash_function)(value_type value), bool (*equality_function)(value_type val1, value_type val2));
void       HT_Destroy(HashTable* table);
value_type HT_search(HashTable* table, value_type find_value);
void       HT_add(HashTable* table, value_type add_value);
size_t*    HT_GetStatistics(HashTable* table);

#endif
