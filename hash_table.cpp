#include "hash_table.h"
#include "stdio.h"

HashTable* HT_Create(key_type (*hash_function)(value_type value)) {
    HashTable* ht = (HashTable*)calloc(1, sizeof(HashTable));
    ht->length = HT_TABLE_SIZE;
    ht->hash_function = hash_function;
    ht->array = (List**)calloc(ht->length, sizeof(List*));
    for (size_t i = 0; i < ht->length; ++i) {
        ht->array[i] = LST_Create();
    }
    return ht;
}

void HT_Destroy(HashTable* table) {
    for (size_t i = 0; i < table->length; ++i) {
        LST_Destroy(table->array[i]);
    }
    free(table->array);
    free(table);
}

bool HT_search(HashTable* table, value_type find_value) {
    key_type find_hash = table->hash_function(find_value);
    return LST_find(table->array[find_hash], find_value);
}

void HT_add(HashTable* table, value_type add_value) {
    key_type add_hash = table->hash_function(add_value);
    LST_add(table->array[add_hash], add_value);
}
