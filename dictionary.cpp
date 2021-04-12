#include "dictionary.h"
#include "stdio.h"

Dictionary* DICT_CreateEmpty(key_type (*hash_function)(value_type value)) {
    Dictionary* dict = (Dictionary*)calloc(1, sizeof(Dictionary));
    dict->table = HT_Create(hash_function, words_equal);
    return dict;
}

void DICT_Destroy(Dictionary* dict) {
    printf("destroying dict\n");
    HT_Destroy(dict->table);
    free(dict);
}

void DICT_ParseFile(Dictionary* dict, char* filename, char separator) {
    FILE* file = NULL;
    open_file(&file, filename, "r");
    char* buffer = NULL;
    uint64_t buf_size = 0;
    read_buffer(&buffer, &buf_size, filename, file);
    char* line = strtok(buffer, "\n");
    while (line != NULL) {
        char* translation = strchr(line, '-');
        printf("yoy\n");
        *translation = '\0';
        ++translation;
        printf("%s\n", line);
        DICT_AddWord(dict, line, translation);
        printf("yeah\n");
        line = strtok(NULL, "\n");
    }
    printf("yeah3\n");
    free(buffer);
    fclose(file);
}

char* DICT_GetTranslation(Dictionary* dict, char* word) {
    printf("dict: getting translation\n");
    Word result = HT_search(dict->table, {word, NULL});
    return result.translation;
}

void DICT_AddWord(Dictionary* dict, char* word, char* translation) {
    char* word_copy        = (char*)calloc(strlen(word) + 1,        sizeof(char));
    char* translation_copy = (char*)calloc(strlen(translation) + 1, sizeof(char));
    assert(word_copy);
    assert(translation_copy);
    strcpy(word_copy, word);
    strcpy(translation_copy, translation);
    printf("adding\n");
    HT_add(dict->table, {word_copy, translation_copy});
}

size_t* DICT_GetTableStat(Dictionary* dict) {
    return HT_GetStatistics(dict->table);
}

size_t DICT_GetTableSize(Dictionary* dict) {
    return dict->table->length;
}
