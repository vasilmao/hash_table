#ifndef HTML_TRANSLATOR_FILE
#define HTML_TRANSLATOR_FILE
#include "file_reader.h"
#include "dictionary.h"
#include <ctype.h>

struct OutBuffer {
    char* str;
    int size;
    int capacity;
};

void HTML_CreateTranslation(Dictionary* dict, char* file_to_translate);
OutBuffer* CreateBuffer();
void IncreaseCapacity(OutBuffer* buffer);
void WriteToBuffer(OutBuffer* buffer, const char* write_str, int write_str_len);
void DestroyBuffer(OutBuffer* buffer);

#endif
