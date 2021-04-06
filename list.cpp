#include "list.h"

List* CreateList() {
    List* new_list = (List*)calloc(1, sizeof(List));
    new_list->capacity = START_CAPACITY;
    new_list->size = 0;
    new_list->array = (value_type*)calloc(new_list->capacity, sizeof(value_type));
    return new_list;
}

void DestroyList(List* list) {
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
    if (size == capacity) {
        increase_capacity(list);
    }
    list->array[length++] = value;
}
