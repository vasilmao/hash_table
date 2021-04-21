#include "hash_table.h"
#include "stdio.h"

HashTable* HT_Create(key_type (*hash_function)(value_type value)) {
    HashTable* ht         = (HashTable*)calloc(1, sizeof(HashTable));
    ht->length            = HT_TABLE_SIZE;
    ht->hash_function     = hash_function;
    ht->array = (List**)calloc(ht->length, sizeof(List*));
    for (size_t i = 0; i < ht->length; ++i) {
        ht->array[i] = LST_Create();
    }
    return ht;
}

void HT_Destroy(HashTable* table) {
    // printf("destr ht: destroying lists\n");
    for (size_t i = 0; i < table->length; ++i) {
        LST_Destroy(table->array[i]);
    }
    // printf("all lists destroyed\n");
    free(table->array);
    // printf("ht array lists destroyed\n");
    free(table);
    // printf("ht destroyed\n");
}

value_type HT_search(HashTable* table, value_type find_value) {
    // printf("ht: getting translation %s\n", find_value.word);
    key_type find_hash = table->hash_function(find_value) % table->length;
    // printf("ht: got %zu\n", find_hash);
    value_type result = LST_search(table->array[find_hash], find_value);
    // printf("%p\n", result.word);
    return result;
}

void HT_add(HashTable* table, value_type add_value) {
    //printf("ht: adding translation %s\n", add_value.word);
    key_type add_hash = table->hash_function(add_value) % table->length;
    //printf("ht: got %zu\n", add_hash);
    LST_add(table->array[add_hash], add_value);
}

size_t* HT_GetStatistics(HashTable* table) {
    size_t* array = (size_t*)calloc(table->length, sizeof(size_t));
    for (size_t i = 0; i < table->length; ++i) {
        array[i] = table->array[i]->length;
    }
    return array;
}
