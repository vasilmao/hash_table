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
    "vmovdqu ymm0, YMMWORD PTR [rsi]\n"
    "mov r10, [rdi]\n" // bucket size
    // "shl r10, 3\n" // bucket size * word size / 2 (8)
    "mov r8, 0\n" // bucket iterator * word size / 2 (8)
    "mov r9, rdi\n"
    "mov r11, [rdi + 16]\n"
    "LstSearchLoop:\n"
        "cmp r8, r10\n"
        "je LstSearchLoopExit\n"
        "mov rdi, [r11]\n" // word, not translation
        "vmovdqa ymm1, YMMWORD PTR [rdi]\n"
        "mov rdx, rsi\n"            // word from argument
        //"push r10\n"
        "xor rax, rax\n"
            "vpcmpeqb ymm3, ymm1, ymm2\n"
            "vpmovmskb eax, ymm3\n"
        // rax - result - equal or not
        //"pop r10\n"
        "test eax, eax\n"              // 0 - false, another - true
        "je LstSearchWrongWord\n"
        "mov rax, [r11]\n" // word
        "mov rdx, [r11 + 8]\n"   // translation
        "ret\n"
        "LstSearchWrongWord:\n"
        "inc r8\n"
        "add r11, 16\n"
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
