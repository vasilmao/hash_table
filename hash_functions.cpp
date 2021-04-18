#include "hash_functions.h"


size_t ror(size_t x);
size_t rol(size_t x);
uint32_t crc32_for_byte(uint32_t r);
void crc32(const void *data, size_t n_bytes, uint32_t* crc);

size_t hash_function_const(Word word) {
    return 1;
}

size_t hash_function_len(Word word) {
    return strlen(word.word);
}

size_t hash_function_first_ascii(Word word) {
    // printf("%d\n", (int)(*word.word));
    return (unsigned char)(*(word.word));
}

size_t hash_function_sum_ascii(Word word) {
    char* s = word.word;
    size_t ans = 0;
    while (*s != '\0') {
        ans += *s;
        s++;
    }
    return ans;
}

size_t ror(size_t x) {
    return (x >> 1) | (x << 63);
}

size_t rol(size_t x) {
    return (x << 1) | (x >> 63);
}

size_t hash_function_ror(Word word) {
    char* s = word.word;
    size_t ans = 0;
    while (*s != '\0') {
        ans = ror(ans) ^ (*s);
        s++;
    }
    return ans;
}

size_t hash_function_rol(Word word) {
    char* s = word.word;
    size_t ans = 0;
    while (*s != '\0') {
        ans = rol(ans) ^ (*s);
        s++;
    }
    return ans;
}


uint32_t crc32_for_byte(uint32_t r) {
  for(int j = 0; j < 8; ++j)
    r = (r & 1? 0: (uint32_t)0xEDB88320L) ^ r >> 1;
  return r ^ (uint32_t)0xFF000000L;
}

void crc32(const void *data, size_t n_bytes, uint32_t* crc) {
  static uint32_t table[0x100];
  if(!*table)
    for(size_t i = 0; i < 0x100; ++i)
      table[i] = crc32_for_byte(i);
  for(size_t i = 0; i < n_bytes; ++i)
    *crc = table[(uint8_t)*crc ^ ((uint8_t*)data)[i]] ^ *crc >> 8;
}

size_t hash_function_crc32(Word word) {
    uint32_t crc_ans = 0;
    crc32(word.word, strlen(word.word), &crc_ans);
    return crc_ans;
}
