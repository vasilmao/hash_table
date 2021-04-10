#include "translation.h"
#include "stdio.h"

bool words_equal(Word word1, Word word2) {
    assert(word1.word);
    assert(word2.word);
    printf("yay compare\n");
    return strcmp(word1.word, word2.word) == 0;
}

void DestroyElement(Word word) {
    free(word.word);
    free(word.translation);
}
