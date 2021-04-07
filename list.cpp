#include "list.h"

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
    free(list->array);
    list->capacity = 0;
    list->length = 0;
    free(list);
}

bool LST_find(List* list, value_type value) {
    for (size_t i = 0; i < list->length; ++i) {
        if (list->array[i] == value) {
            return true;
        }
    }
    return false;
}

void LST_add(List* list, value_type value) {
    if (list->length == list->capacity) {
        increase_capacity(list);
    }
    list->array[list->length++] = value;
}
