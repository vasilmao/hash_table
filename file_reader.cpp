#include "file_reader.h"

uint64_t get_file_size(const char *filename) {
    assert(filename);
    struct stat filestats;
    int res = stat(filename, &filestats);
    if (res != 0){
        printf("Не удалось получить размер файла %s\n", filename);
        assert(res != 0);
    }
    return filestats.st_size;
}

void open_file(FILE **file, const char *filename, const char *mode) {
    assert(file);
    assert(filename);
    *file = fopen(filename, mode);
    if (*file == NULL) {
        printf("Ошибка открытия файла %s\n", filename);
    }
    assert(*file);
}

void read_buffer(char** buffer, uint64_t* buffer_size, const char* input_filename, FILE* input) {
    assert(buffer);
    assert(input_filename);
    assert(input);
    *buffer_size = get_file_size(input_filename) + 1;

    *buffer = (char *) calloc(*buffer_size, sizeof(char));
    *buffer_size = fread(*buffer, sizeof(char), *buffer_size, input);
    //fclose(input);
    //fread не ставит '\0' в конце
    (*buffer)[*buffer_size] = '\0';
}
