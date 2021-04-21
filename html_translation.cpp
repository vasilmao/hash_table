#include "dictionary.h"
#include "html_translator.h"
#include "hash_functions.h"

// this is main file for html dict

int main(int argc, char* argv[]) {
    assert(argc == 2);
    Dictionary* dict = DICT_CreateEmpty(hash_function_crc32);
    DICT_ParseFile(dict, "dic.txt", '\n');
    HTML_CreateTranslation(dict, argv[1]);
    DICT_Destroy(dict);
}
