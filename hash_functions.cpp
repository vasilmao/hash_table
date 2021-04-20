#include "hash_functions.h"
//#include <nmmintrin.h>


size_t ror(size_t x);
size_t rol(size_t x);

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


// uint32_t crc32_for_byte(uint32_t r) {
//   for(int j = 0; j < 8; ++j)
//     r = (r & 1? 0: (uint32_t)0xEDB88320L) ^ r >> 1;
//   return r ^ (uint32_t)0xFF000000L;
// }

const uint32_t crc_table[256] = {3523407757,2768625435,1007455905,1259060791,3580832660,2724731650,996231864,1281784366,3705235391,2883475241,852952723,1171273221,3686048678,2897449776,901431946,1119744540,3484811241,3098726271,565944005,1455205971,3369614320,3219065702,651582172,1372678730,3245242331,3060352845,794826487,1483155041,3322131394,2969862996,671994606,1594548856,3916222277,2657877971,123907689,1885708031,3993045852,2567322570,1010288,1997036262,3887548279,2427484129,163128923,2126386893,3772416878,2547889144,248832578,2043925204,4108050209,2212294583,450215437,1842515611,4088798008,2226203566,498629140,1790921346,4194326291,2366072709,336475711,1661535913,4251816714,2322244508,325317158,1684325040,2766056989,3554254475,1255198513,1037565863,2746444292,3568589458,1304234792,985283518,2852464175,3707901625,1141589763,856455061,2909332022,3664761504,1130791706,878818188,3110715001,3463352047,1466425173,543223747,3187964512,3372436214,1342839628,655174618,3081909835,3233089245,1505515367,784033777,2967466578,3352871620,1590793086,701932520,2679148245,3904355907,1908338681,112844655,2564639436,4024072794,1993550816,30677878,2439710439,3865851505,2137352139,140662621,2517025534,3775001192,2013832146,252678980,2181537457,4110462503,1812594589,453955339,2238339752,4067256894,1801730948,476252946,2363233923,4225443349,1657960367,366298937,2343686810,4239843852,1707062198,314082080,1069182125,1220369467,3518238081,2796764439,953657524,1339070498,3604597144,2715744526,828499103,1181144073,3748627891,2825434405,906764422,1091244048,3624026538,2936369468,571309257,1426738271,3422756325,3137613171,627095760,1382516806,3413039612,3161057642,752284923,1540473965,3268974039,3051332929,733688034,1555824756,3316994510,2998034776,81022053,1943239923,3940166985,2648514015,62490748,1958656234,3988253008,2595281350,168805463,2097738945,3825313147,2466682349,224526414,2053451992,3815530850,2490061300,425942017,1852075159,4151131437,2154433979,504272920,1762240654,4026595636,2265434530,397988915,1623188645,4189500703,2393998729,282398762,1741824188,4275794182,2312913296,1231433021,1046551979,2808630289,3496967303,1309403428,957143474,2684717064,3607279774,1203610895,817534361,2847130659,3736401077,1087398166,936857984,2933784634,3654889644,1422998873,601230799,3135200373,3453512931,1404893504,616286678,3182598252,3400902906,1510651243,755860989,3020215367,3271812305,1567060338,710951396,3010007134,3295551688,1913130485,84884835,2617666777,3942734927,1969605100,40040826,2607524032,3966539862,2094237127,198489425,2464015595,3856323709,2076066270,213479752,2511347954,3803648100,1874795921,414723335,2175892669,4139142187,1758648712,534112542,2262612132,4057696306,1633981859,375629109,2406151311,4167943193,1711886778,286155052,2282172566,4278190080};

// void crc32(const void *data, size_t n_bytes, uint32_t* crc) {
//     // static uint32_t table[0x100];
//     // if(!*table)
//     // for(size_t i = 0; i < 0x100; ++i) {
//     //     table[i] = crc32_for_byte(i);
//     //     printf("%zu %u\n", i, table[i]);
//     // }
//     for(size_t i = 0; i < n_bytes; ++i) {
//         *crc = crc_table[(uint8_t)*crc ^ ((uint8_t*)data)[i]] ^ *crc >> 8;
//     }
// }

// asm(".intel_syntax noprefix\n"
// ".globl hash_function_crc32\n"
//     ".type hash_function_crc32, @function\n"
//     "hash_function_crc32:\n"
//     "xor rax, rax\n"
//     "xor rdx, rdx\n"
//     "push rdi\n"
//     "call strlen@PLT\n"
//     "mov edx, eax\n"
//     "pop rdi\n"
//     "xor rax, rax\n"
//     "crcloop:\n"
//         "cmp rdx, 8\n"
//         "jae Crc64\n"
//         "crclooplow:"
//         "cmp rdx, 0\n"
//         "je crcloopexit\n"
//         "crc32 rax, byte ptr [rdi]\n"
//         "inc rdi\n"
//         "dec rdx\n"
//         "jmp crclooplow\n"
//         "Crc64:\n"
//         "crc32 rax, qword ptr [rdi]\n"
//         "add rdi, 8\n"
//         "sub rdx, 8\n"
//         "jmp crcloop\n"
//     "crcloopexit:\n"
//     //"xor rax, rax\n"
//     "ret\n"
//     ".att_syntax noprefix\n"
// );

void crc32(const void *data, size_t n_bytes, uint32_t* crc) {
    for(size_t i = 0; i < n_bytes; ++i)
        *crc = crc_table[(uint8_t)*crc ^ ((uint8_t*)data)[i]] ^ *crc >> 8;
}

size_t hash_function_crc32(Word word) {
    uint32_t crc_ans = 0;
    crc32(word.word, strlen(word.word), &crc_ans);
    return crc_ans;
}

// size_t hash_function_crc32(Word word) {
//     uint32_t crc_ans = 0;
//     int length = strlen(word.word);
//     char* data = word.word;
//     for (int i = 0; i < length; ++i) {
//         crc_ans = _mm_crc32_u8(crc_ans, data[i]);
//     }
//     //printf("%zu %zu\n", crc_ans,  hash_function_crc32_1(word));
//     return crc_ans;
// }
