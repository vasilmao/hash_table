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
};

List*      LST_Create();
void       LST_Destroy(List* list);
extern "C" value_type LST_search(List* list, value_type value);
void       LST_add(List* list, value_type value);

#endif
