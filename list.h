#ifndef ListFile
#define ListFile

typedef char*  value_type
const int START_CAPACITY = 10;


struct List {
    size_t length;
    size_t capacity;
    value_type* array;
};

List* LST_Create();
void LST_DestroyList(List* list);
bool LST_find(List* list, value_type value);

#endif
