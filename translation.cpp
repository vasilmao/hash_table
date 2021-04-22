#include "translation.h"
#include "stdio.h"

bool words_equal(Word word1, Word word2) {
    return strcmp(word1.word, word2.word) == 0;
}


// rdi, rdx - arguments
// damage rcx, rax, rdi, rdx
// asm(".intel_syntax noprefix\n"
// ".text\n"
// ".globl words_equal\n"
//     ".type words_equal, @function\n"
//     "words_equal:\n"
//     "xor rcx, rcx\n"
//     "StrcmpLoop:\n"
//         "xor rcx, rcx\n"
//         "mov cl, byte ptr [rdi]\n"
//         "cmp cl, byte ptr [rdx]\n"
//         "jne LoopExit\n"
//         "inc rdi\n"
//         "inc rdx\n"
//         "cmp cl, 0\n"
//         "jne StrcmpLoop\n"
//         "mov rax, 0xffff\n"
//         "ret\n"
//     "LoopExit:\n"
//     "xor rax, rax\n"
//     "ret\n"
//     ".att_syntax noprefix\n"
// );

void DestroyElement(Word word) {
    free(word.word);
    free(word.translation);
}
