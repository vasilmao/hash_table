#include "stdio.h"
#include "dictionary.h"
#include "hash_functions.h"

const int HASH_FUNCTIONS_CNT = 7;



int write_arr_to_buffer(size_t* array, size_t cnt, char* buffer) {
    int written_cnt = 0;

    for (int i = 0; i < cnt - 1; ++i) {
        written_cnt += sprintf(buffer + written_cnt, "%zu,", array[i]);
        // buffer += written_cnt;
    }
    written_cnt += sprintf(buffer + written_cnt, "%zu\n", array[cnt - 1]);
    return written_cnt;
}

#define TEST_HF(hf) {                                                              \
    dict = DICT_CreateEmpty(hf);                                                   \
    DICT_ParseFile(dict, "dic.txt", '\n');                                         \
    stats = DICT_GetTableStat(dict);                                               \
    written_cnt += write_arr_to_buffer(stats, ht_size, out_buffer + written_cnt);  \
    DICT_Destroy(dict);                                                            \
    free(stats);                                                                   \
}

int main() {
    Dictionary* dict = DICT_CreateEmpty(hash_function_const);
    size_t ht_size = DICT_GetTableSize(dict);
    DICT_Destroy(dict);

    char* out_buffer = (char*)calloc((ht_size * (sizeof(size_t) + 1)) * HASH_FUNCTIONS_CNT, sizeof(char));
    int written_cnt = 0;
    size_t* stats = NULL;
    TEST_HF(hash_function_const);
    TEST_HF(hash_function_len);
    TEST_HF(hash_function_first_ascii);
    TEST_HF(hash_function_sum_ascii);
    TEST_HF(hash_function_ror);
    TEST_HF(hash_function_rol);
    TEST_HF(hash_function_crc32);

    FILE* out_file;
    open_file(&out_file, "out.csv", "w");
    fwrite(out_buffer, written_cnt, sizeof(char), out_file);
    fclose(out_file);
    free(out_buffer);
    return 0;
}
