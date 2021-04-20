#ifndef LIST_FILE
#define LIST_FILE

#include "stdlib.h"
#include "translation.h"

typedef Word  value_type;
const int START_CAPACITY = 10;


struct List {
    size_t      length;
    size_t      capacity;
    value_type* array;
    bool        (*equality_function)(value_type val1, value_type val2);
};

List*      LST_Create(bool (*equality_function)(value_type val1, value_type val2));
void       LST_Destroy(List* list);
value_type LST_search(List* list, value_type value);
void       LST_add(List* list, value_type value);

#endif
