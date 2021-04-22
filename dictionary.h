#ifndef DICTIONARY_FILE
#define DICTIONARY_FILE
#include "hash_table.h"
#include "translation.h"
#include "file_reader.h"

struct Dictionary {
    HashTable* table;
    char* buffer;
    char* buffer_start;
    size_t buffer_size;
    size_t buffer_capacity;
};

Dictionary* DICT_CreateEmpty(key_type (*hash_function)(value_type value));
void        DICT_Destroy();
void        DICT_ParseFile(Dictionary* dict, char* filename, char separator);
char*       DICT_GetTranslation(Dictionary* dict, char* word);
void        DICT_AddWord(Dictionary* dict, char* word, char* translation);
size_t*     DICT_GetTableStat(Dictionary* dict);
size_t      DICT_GetTableSize(Dictionary* dict);
void        DICT_Destroy(Dictionary* dict);

#endif
