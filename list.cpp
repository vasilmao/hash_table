#include "list.h"
#include "stdio.h"

void increase_capacity(List* list);

void increase_capacity(List* list) {
    list->capacity *= 2;
    list->array = (value_type*)realloc(list->array, list->capacity * sizeof(value_type));
}

List* LST_Create(bool (*equality_function)(value_type val1, value_type val2)) {
    List* new_list = (List*)calloc(1, sizeof(List));
    new_list->equality_function = equality_function;
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

value_type LST_search(List* list, value_type value) {
    printf("list: getting trans\n");
    for (size_t i = 0; i < list->length; ++i) {
        if (list->equality_function(list->array[i], value)) {
            printf("yeah equality\n");
            return list->array[i];
        }
    }
    return NULL_WORD;
}

void LST_add(List* list, value_type value) {
    assert(list);
    printf("%p\n", list);
    list->length;
    printf("yeah\n");
    printf("%zu\n", list->length);
    printf("%zu\n", list->capacity);
    printf("yoy\n");
    if (list->length == list->capacity) {
        printf("increasing\n");
        increase_capacity(list);
    }
    list->array[list->length++] = value;
}
