#ifndef TRANSLATION_FILE
#define TRANSLATION_FILE
#include "string.h"
#include "stdlib.h"
#include "assert.h"

struct Word {
    char* word;
    char* translation;
};

const Word NULL_WORD = {NULL, NULL};

extern "C" bool words_equal(Word word1, Word word2);
void DestroyElement(Word word);

#endif
