#include "stdio.h"
#include "dictionary.h"

size_t hf(Word word) {
    printf("yay hf\n");
    return 1;
}

int main() {
    Dictionary* dict = DICT_CreateEmpty(hf);
    printf("yeah1\n");
    DICT_AddWord(dict, "keklol", "zalupa");
    printf("yeah2\n");
    printf("%s\n", DICT_GetTranslation(dict, "keklol"));
    printf("yeah3\n");
    DICT_Destroy(dict);
    printf("yeah4\n")
