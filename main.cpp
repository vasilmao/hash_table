#include "stdio.h"
#include "hash_table.h"

size_t hf(char* s) {
    printf("yay hf\n");
    return 1;
}

int main() {
    HashTable* ht = HT_Create(hf);
    printf("yeah1\n");
    HT_add(ht, "keklol");
    printf("yeah2\n");
    printf("%d\n", (int)HT_search(ht, "keklol"));
    printf("yeah3\n");
    HT_Destroy(ht);
    printf("yeah4\n");
}
