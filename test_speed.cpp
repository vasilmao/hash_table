#include "dictionary.h"
#include "html_translator.h"
#include "hash_functions.h"

const int test_num = 150000;
const int max_word_len = 20;

void DoTests(Dictionary* dict);

int main() {
    Dictionary* dict = DICT_CreateEmpty(hash_function_crc32);
    DICT_ParseFile(dict, "dic.txt", '\n');
    DoTests(dict);
    DICT_Destroy(dict);
}

void DoTests(Dictionary* dict) {
    char* current_word = (char*) calloc(max_word_len + 1, sizeof(char));
    for (int i = 0; i < test_num; ++i) {
        int word_len = rand() % max_word_len;
        for (int j = 0; j < word_len; ++j) {
            current_word[j] = rand() % 128;
        }
        current_word[word_len] = 0;
        for (int j = 0; j < 100; ++j) {
            volatile char* ans = DICT_GetTranslation(dict, current_word);
        }
    }
    free(current_word);
}
