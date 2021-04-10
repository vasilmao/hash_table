#include "dictionary.h"
#include ".h"
#include "stdio.h"

Dictionary* DICT_CreateEmpty(key_type (*hash_function)(value_type value)) {
    Dictionary* dict = (Dictionary*)calloc(1, sizeof(Dictionary));
    dict->table = HT_Create(hash_function, words_equal);
    return dict;
}

void DICT_Destroy(Dictionary* dict) {
    HT_Destroy(dict->table);
    free(dict);
}

void DICT_ParseFile(Dictionary* dict, char* filename, char separator) {

}

char* DICT_GetTranslation(Dictionary* dict, char* word) {
    printf("dict: getting translation\n");
    Word result = HT_search(dict->table, {word, NULL});
    return result.translation;
}

void DICT_AddWord(Dictionary* dict, char* word, char* translation) {
    char* word_copy        = (char*)calloc(strlen(word) + 1,        sizeof(char));
    char* translation_copy = (char*)calloc(strlen(translation) + 1, sizeof(char));
    strcpy(word_copy, word);
    strcpy(translation_copy, translation);
    HT_add(dict->table, {word_copy, translation_copy});
}

size_t* DICT_GetTableStat(Dictionary* dict) {
    return HT_GetStatistics(dict->table);
}

size_t DICT_GetTableSize(Dictionary* dict) {
    return dict->table->length;
}
