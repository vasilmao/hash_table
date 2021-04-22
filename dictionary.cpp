#include "dictionary.h"
#include "stdio.h"

void AddToBuffer(char* word, char* translation);

Dictionary* DICT_CreateEmpty(key_type (*hash_function)(value_type value)) {
    Dictionary* dict = (Dictionary*)calloc(1, sizeof(Dictionary));
    dict->table = HT_Create(hash_function);
    dict->buffer_size = 0;
    dict->buffer_capacity = 1024;
    dict->buffer_start = (char*)calloc(dict->buffer_capacity + 64, sizeof(char));
    dict->buffer = dict->buffer_start;
    while ((size_t)dict->buffer & 63) {
        ++dict->buffer;
    }
    return dict;
}

void DICT_Destroy(Dictionary* dict) {
    HT_Destroy(dict->table);
    free(dict->buffer_start);
    free(dict);
}

void AddToBuffer(Dictionary* dict, char* word, char* translation) {
    if (dict->buffer_capacity - dict->buffer_size < 64) {
        dict->buffer_capacity <<= 1;
        dict->buffer_start = (char*)realloc(dict->buffer_start, (dict->buffer_capacity + 64) * sizeof(char));
        dict->buffer = dict->buffer_start;
        while ((size_t)dict->buffer & 63) {
            ++dict->buffer;
        }
    }
    strcpy(dict->buffer + dict->buffer_size, word);
    dict->buffer_size += 32;
    //char* translation_copy_utf8 = EncodeCyrillicWithUtf8(translation);
    strcpy(dict->buffer + dict->buffer_size, translation);
    dict->buffer_size += 32;
    //free(translation_copy_utf8);
}



void DICT_ParseFile(Dictionary* dict, char* filename, char separator) {
    FILE* file = NULL;
    open_file(&file, filename, "r");
    char* buffer = NULL;
    uint64_t buf_size = 0;
    read_buffer(&buffer, &buf_size, filename, file);
    char* line = strtok(buffer, "\r\n");
    while (line != NULL) {
        char* translation = strchr(line, '-');
        if (translation == NULL) {
            line = strtok(NULL, "\r\n");
            continue;
        }
        *translation = '\0';
        ++translation;
        AddToBuffer(dict, line, translation);
        //DICT_AddWord(dict, line, translation);
        // printf("%s %s\n", line, translation);
        line = strtok(NULL, "\r\n");
    }
    for (size_t i = 0; i < dict->buffer_size; i += 64) {
        DICT_AddWord(dict, dict->buffer + i, dict->buffer + (i + 32));
    }
    free(buffer);
    fclose(file);
    // printf("file parsed\n");
}

char* DICT_GetTranslation(Dictionary* dict, char* word) {
    // printf("dict: searching %s\n", word);
    Word result = HT_search(dict->table, {word, NULL});
    return result.translation;
}

void DICT_AddWord(Dictionary* dict, char* word, char* translation) {
    HT_add(dict->table, {word, translation});
}

size_t* DICT_GetTableStat(Dictionary* dict) {
    return HT_GetStatistics(dict->table);
}

size_t DICT_GetTableSize(Dictionary* dict) {
    return dict->table->length;
}
