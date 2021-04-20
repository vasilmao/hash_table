#include "dictionary.h"
#include "stdio.h"

char* EncodeCyrillicWithUtf8(char* word);

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
        DICT_AddWord(dict, line, translation);
        if (translation)
        line = strtok(NULL, "\r\n");
    }
    free(buffer);
    fclose(file);
}

char* DICT_GetTranslation(Dictionary* dict, char* word) {
    Word result = HT_search(dict->table, {word, NULL});
    return result.translation;
}

void DICT_AddWord(Dictionary* dict, char* word, char* translation) {
    char* word_copy = (char*)calloc(strlen(word) + 1, sizeof(char));
    assert(word_copy);
    strcpy(word_copy, word);
    char* translation_copy_utf8 = EncodeCyrillicWithUtf8(translation);
    HT_add(dict->table, {word_copy, translation_copy_utf8});
}

char* EncodeCyrillicWithUtf8(char* word) {
    int len = strlen(word);
    char* new_word = (char*)calloc(len * 2 + 1, sizeof(char));
    char* new_word_start = new_word;
    assert(new_word);
    while (*word != '\0') {
        if (*word >= 0) {
            *(new_word++) = *word;
        } else if (*word <= -17) {
            *(new_word++) = 0xd0;
            *(new_word++) = (*word + 32) + 0xb0;
        } else if (*word == -72) {
            *(new_word++) = 0xd1;
            *(new_word++) = 0x91;
        } else {
            *(new_word++) = 0xd1;
            *(new_word++) = (*word + 16) + 0x80;
        }
        ++word;
    }
    return new_word_start;
}

size_t* DICT_GetTableStat(Dictionary* dict) {
    return HT_GetStatistics(dict->table);
}

size_t DICT_GetTableSize(Dictionary* dict) {
    return dict->table->length;
}
