#include "html_translator.h"

void HTML_CreateTranslation(Dictionary* dict, char* file_to_translate) {
    printf("kek\n");
    FILE* input_file = NULL;
    open_file(&input_file, file_to_translate, "r");
    uint64_t buffer_size = 0;
    char* buffer = NULL;
    read_buffer(&buffer, &buffer_size, file_to_translate, input_file);
    char* word = strtok(buffer, " \n\t");
    char* current_word = (char*)calloc(100, sizeof(char));
    OutBuffer* out_buffer = CreateBuffer();
    printf("yoy\n");
    while (word != NULL) {
        char* word_end = word;
        int len = 0;
        while (isalpha(*(word_end))) {
            ++word_end;
            ++len;
        }
        if (len > 100) {
            // no such word
        }
        strncpy(current_word, word, len);
        current_word[len] = '\0';
        //printf("%s", current_word);
        WriteToBuffer(out_buffer, "<div title=\"", 12);
        char* translation = DICT_GetTranslation(dict, current_word);
        if (translation == NULL) {
            WriteToBuffer(out_buffer, "No such word\">", 14);
        } else {
            WriteToBuffer(out_buffer, translation, strlen(translation) - 1);
            WriteToBuffer(out_buffer, "\">", 2);
        }
        WriteToBuffer(out_buffer, current_word, len);
        WriteToBuffer(out_buffer, word_end, strlen(word_end));
        WriteToBuffer(out_buffer, "</div>", 6);
        word = strtok(NULL, " \n\t");
    }
    printf("%s\n", out_buffer->str);
    FILE* out_file = NULL;
    open_file(&out_file, "lol.html", "w");
    fwrite(out_buffer->str, sizeof(char), out_buffer->size, out_file);
    fclose(out_file);
    printf("yeah\n");
}

OutBuffer* CreateBuffer() {
    OutBuffer* buf = (OutBuffer*)calloc(1, sizeof(OutBuffer));
    buf->str = (char*)calloc(100, sizeof(char));
    buf->capacity = 100;
}

void IncreaseCapacity(OutBuffer* buffer) {
    buffer->capacity *= 2;
    buffer->str = (char*)realloc(buffer->str, buffer->capacity * sizeof(char));
}

void WriteToBuffer(OutBuffer* buffer, char* write_str, int write_str_len) {
    printf("was: %s\n", buffer->str);
    while (write_str_len > buffer->capacity - buffer->size) {
        IncreaseCapacity(buffer);
    }
    strncpy(buffer->str + buffer->size, write_str, write_str_len);
    buffer->size += write_str_len;
    printf("now: %s\n", buffer->str);
}

void DestroyBuffer(OutBuffer* buffer) {
    free(buffer->str);
    free(buffer);
}
