#include "translation.h"
#include "stdio.h"
    //assert(word1.word);
    //assert(word2.word);
    // printf("yay compare\n");
//     return strcmp(word1.word, word2.word) == 0;
// }

// rdi, rdx - arguments
asm(".intel_syntax noprefix\n"
".globl words_equal\n"
    ".type words_equal, @function\n"
    "words_equal:\n"
    "StrcmpLoop:\n"
        "mov bl, byte [rdi]\n"
        "mov bh, byte [rdx]\n"
        "cmp bl, bh\n"
        "jne LoopExit\n"
        "cmp bl, 0\n"
        "inc rdi\n"
        "inc rdx\n"
        "jne StrcmpLoop\n"
        "mov rax, 1\n"
        "ret\n"
    "LoopExit:\n"
    //"xor rax, rax\n"
    "ret\n"
    ".att_syntax noprefix\n"
);

void DestroyElement(Word word) {
    free(word.word);
    free(word.translation);
}
