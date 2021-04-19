#include "html_translator.h"

const char* div_start     = "<div style=\"display: inline\"title=\"";
const int   div_start_len = strlen(div_start);

const char* div_end       = "</div>";
const int   div_end_len   = strlen(div_end);



char* FindNextToken(char* string);

void HTML_CreateTranslation(Dictionary* dict, char* file_to_translate) {
    printf("kek\n");
    FILE* input_file = NULL;
    open_file(&input_file, file_to_translate, "r");
    uint64_t buffer_size = 0;
    char* buffer = NULL;
    read_buffer(&buffer, &buffer_size, file_to_translate, input_file);
    char* word = buffer;
    char* current_word = (char*)calloc(100, sizeof(char));
    OutBuffer* out_buffer = CreateBuffer();
    printf("yoy\n");
    int cnt = 0;
    while (*word != '\0') {
        cnt += 1;
        // if (cnt == 30) {
        //     break;
        // }
        char* word_end = word;
        int len = 0;
        while (isalpha(*(word_end))) {
            ++word_end;
            ++len;
        }
        if (len > 100) {
            // no such word
        }
        if (len == 0) {\
            if (*word == '\n') {
                WriteToBuffer(out_buffer, "<br>", 4);
            }
            WriteToBuffer(out_buffer, word, 1);
            word++;
            continue;
        }
        strncpy(current_word, word, len);
        current_word[len] = '\0';
        for (int i = 0; i < len; ++i) {
            current_word[i] = tolower(current_word[i]);
        }
        printf("%s\n", current_word);
        WriteToBuffer(out_buffer, div_start, div_start_len);
        char* translation = DICT_GetTranslation(dict, current_word);
        if (translation == NULL) {
            WriteToBuffer(out_buffer, "No such word\">", 14);
        } else {
            printf("yey\n");
            printf("ya %s ok\n", translation);
            printf("yey 2\n");
            WriteToBuffer(out_buffer, translation, strlen(translation));
            WriteToBuffer(out_buffer, "\">", 2);
        }
        printf("yeah\n");
        WriteToBuffer(out_buffer, word, len);
        //WriteToBuffer(out_buffer, word_end, strlen(word_end));
        word = FindNextToken(word_end);
        printf("%p, %p, %d\n", word, word_end, (int)(word - word_end));
        WriteToBuffer(out_buffer, word_end, word - word_end);
        WriteToBuffer(out_buffer, div_end, div_end_len);
        // word = strtok(NULL, " \n\t");
    }
    printf("%s\n", out_buffer->str);
    FILE* out_file = NULL;
    open_file(&out_file, "lol.html", "w");
    fwrite(out_buffer->str, sizeof(char), out_buffer->size, out_file);
    fclose(out_file);
    printf("yeah\n");
}

char* FindNextToken(char* string) {
    printf("%c\n", *string);
    while (!isalpha(*string)) {
        if (*string == '\0' || *string == '\n') {
            return string;
        }
        ++string;
        printf("%c\n", *string);
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
    //printf("kkk1 %p\n", buffer->str);
    //printf("was: %s\n", buffer->str);
    while (write_str_len > buffer->capacity - buffer->size) {
        IncreaseCapacity(buffer);
    }
    //printf("kkk2 %p %p\n", buffer->str, write_str);
    //printf("adding: %s %d\n", write_str, write_str_len);
    strncpy(buffer->str + buffer->size, write_str, write_str_len);
    buffer->size += write_str_len;
    //printf("kkk3 %p\n", buffer->str);
    //printf("now: %s\n", buffer->str);
}

void DestroyBuffer(OutBuffer* buffer) {
    free(buffer->str);
    free(buffer);
}
