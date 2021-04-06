#include "hash_table.h"

bool HT_search(HashTable* table, value_type* find_value) {
    key_type find_hash = table->hash_function(find_key);
    return LST_find(table->array + find_hash, find_value);
}
