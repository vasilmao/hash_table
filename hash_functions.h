#ifndef HASH_FUNCTIONS_FILE
#define HASH_FUNCTIONS_FILE
#include <cstdint>
#include <stdio.h>
#include <stdlib.h>
#include "translation.h"

size_t hash_function_const(Word word);
size_t hash_function_len(Word word);
size_t hash_function_first_ascii(Word word);
size_t hash_function_sum_ascii(Word word);
size_t hash_function_ror(Word word);
size_t hash_function_rol(Word word);
size_t hash_function_crc32(Word word);
// size_t hash_function_crc32(Word word);

#endif
