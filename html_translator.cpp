#include "html_translator.h"

const char* div_start     = "<div style=\"display: inline\"title=\"";
const int   div_start_len = strlen(div_start);

const char* div_end       = "</div>";
const int   div_end_len   = strlen(div_end);



char* FindNextToken(char* string);
void ToLower(char* word, int length);

void HTML_CreateTranslation(Dictionary* dict, const char* file_to_translate) {
    FILE* input_file = NULL;
    open_file(&input_file, file_to_translate, "r");

    uint64_t buffer_size = 0;
    char* buffer = NULL;
    read_buffer(&buffer, &buffer_size, file_to_translate, input_file);
    fclose(input_file);

    char* word = buffer;
    char* current_word = (char*)calloc(100, sizeof(char));
    OutBuffer* out_buffer = CreateBuffer();

    while (*word != '\0') {
        char* word_end = word;
        int len = 0;
        while (isalpha(*(word_end))) {
            ++word_end;
            ++len;
        }

        if (len > 100) {
            WriteToBuffer(out_buffer, word, len);
            word = FindNextToken(word_end);
            continue;
        }

        if (len == 0) {
            if (*word == '\n') {
                WriteToBuffer(out_buffer, "<br>", 4);
            }
            WriteToBuffer(out_buffer, word, 1);
            word++;
            continue;
        }

        strncpy(current_word, word, len);
        current_word[len] = '\0';
        ToLower(current_word, len);

        WriteToBuffer(out_buffer, div_start, div_start_len);
        char* translation = DICT_GetTranslation(dict, current_word);
        if (translation == NULL) {
            WriteToBuffer(out_buffer, "No such word\">", 14);
        } else {
            WriteToBuffer(out_buffer, translation, strlen(translation));
            WriteToBuffer(out_buffer, "\">", 2);
        }
        WriteToBuffer(out_buffer, word, len);
        word = FindNextToken(word_end);
        WriteToBuffer(out_buffer, word_end, word - word_end);
        WriteToBuffer(out_buffer, div_end, div_end_len);
    }
    FILE* out_file = NULL;
    open_file(&out_file, "translation.html", "w");
    fwrite(out_buffer->str, sizeof(char), out_buffer->size, out_file);

    fclose(out_file);
    DestroyBuffer(out_buffer);
    free(current_word);
    free(buffer);
}

void ToLower(char* word, int length) {
    for (int i = 0; i < length; ++i) {
        word[i] = tolower(word[i]);
    }
}

char* FindNextToken(char* string) {
    while (!isalpha(*string)) {
        if (*string == '\0' || *string == '\n') {
            return string;
        }
        ++string;
    }
    return string;
}

OutBuffer* CreateBuffer() {
    OutBuffer* buf = (OutBuffer*)calloc(1, sizeof(OutBuffer));
    buf->str = (char*)calloc(100, sizeof(char));
    buf->capacity = 100;
    return buf;
}

void IncreaseCapacity(OutBuffer* buffer) {
    buffer->capacity *= 2;
    buffer->str = (char*)realloc(buffer->str, (buffer->capacity + 1) * sizeof(char));
}

void WriteToBuffer(OutBuffer* buffer, const char* write_str, int write_str_len) {
    while (write_str_len > buffer->capacity - buffer->size) {
        IncreaseCapacity(buffer);
    }
    strncpy(buffer->str + buffer->size, write_str, write_str_len);
    buffer->size += write_str_len;
}

void DestroyBuffer(OutBuffer* buffer) {
    free(buffer->str);
    free(buffer);
}
