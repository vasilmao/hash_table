#include "list.h"
#include "stdio.h"

void increase_capacity(List* list);

void increase_capacity(List* list) {
    list->capacity *= 2;
    list->array = (value_type*)realloc(list->array, list->capacity * sizeof(value_type));
}

List* LST_Create() {
    List* new_list = (List*)calloc(1, sizeof(List));
    new_list->capacity = START_CAPACITY;
    new_list->length = 0;
    new_list->array = (value_type*)calloc(new_list->capacity, sizeof(value_type));
    return new_list;
}

void LST_Destroy(List* list) {
    for (size_t i = 0; i < list->length; ++i) {
        DestroyElement(list->array[i]);
    }
    free(list->array);
    list->capacity = 0;
    list->length = 0;
    free(list);
}

//rdi - List*, rsi - word
//to return: rdx:rax
asm(".intel_syntax noprefix\n"
".globl LST_search\n"
    ".type LST_search, @function\n"
    "LST_search:\n"
    "mov r10, [rdi]\n" // bucket size
    "shl r10, 3\n" // bucket size * word size / 2 (8)
    "mov r8, 0\n" // bucket iterator * word size / 2 (8)
    "mov r9, rdi\n"
    "LstSearchLoop:\n"
        "cmp r8, r10\n"
        "je LstSearchLoopExit\n"
        "mov rdi, [r9 + 16]\n" // array of value_type*
        "mov rdi, [rdi + r8 * 2]\n" // word, not translation
        "mov rdx, rsi\n"            // word from argument
        "push r10\n"
            "xor rcx, rcx\n"
            "StrcmpLoop:\n"
                "xor rcx, rcx\n"
                "mov cl, byte ptr [rdi]\n"
                "cmp cl, byte ptr [rdx]\n"
                "jne LoopExit\n"
                "inc rdi\n"
                "inc rdx\n"
                "cmp cl, 0\n"
                "jne StrcmpLoop\n"
                "mov rax, 1\n"
                "jmp WordCompareExit\n"
            "LoopExit:\n"
            "xor rax, rax\n"
            "WordCompareExit:"
        // rax - result - equal or not
        "pop r10\n"
        "cmp rax, 0\n"              // 0 - false, another - true
        "je LstSearchWrongWord\n"
        "mov rdi, [r9 + 16]\n"     // array
        "mov rax, [rdi + r8 * 2]\n" // word
        "mov r9, 8\n"
        "shl r8, 1\n" // r8 * 2
        "add r8, r9\n" // r8 * 3
        "mov rdx, [rdi + r8]\n"   // translation
        "ret\n"
        "LstSearchWrongWord:\n"
        "add r8, 8\n"
        "jmp LstSearchLoop\n"
    "LstSearchLoopExit:\n"
    "xor rax, rax\n"
    "xor rdx, rdx\n"
    "ret\n"
    ".att_syntax noprefix\n"
);

// value_type LST_search(List* list, value_type value) {
//     //printf("searching for %s kek %zu lol\n", value.word, list->length);
//     for (size_t i = 0; i < list->length; ++i) {
//         //printf("%d\n",(int)list->equality_function({"luck", NULL}, value));
//         //printf("%d\n",(int)list->equality_function({"luck", NULL}, list->array[0]));
//         //printf("%d\n",(int)list->equality_function(list->array[i], value));
//         //printf("bruh %zu %s\n", i,  list->array[i].word);
//         if (list->equality_function(list->array[i], value)) {
//             return list->array[i];
//         }
//     }
//     return NULL_WORD;
// }

void LST_add(List* list, value_type value) {
    assert(list);
    // printf("%p\n", list);
    list->length;
    // printf("yeah\n");
    // printf("%zu\n", list->length);
    // printf("%zu\n", list->capacity);
    // printf("yoy\n");
    if (list->length == list->capacity) {
        // printf("increasing\n");
        increase_capacity(list);
    }
    list->array[list->length++] = value;
}
