# hash_table
In this project I'm creating dictionary to translate words form english to russian. I will use hash table, all hash functions return size_t aka unsigned long long int, hash table implemented with buckets aka List.
## 1. Hash functions test
So, hash table can have different hash function. Current test include 7 different hash functions:
1. Returns constant integer (for example 1)
2. Returns word length
3. Returns first ascii number
4. Returns summ of word's ascii numbers
5. h[0] = 0, h[i] = ror(h[i-1]) xor word[i - 1]
6. h[0] = 0, h[i] = rol(h[i-1]) xor word[i - 1]
7. crc32

Dictionary in dic.txt, let's see results
### 1.1 constant
![HF1](/graphs/HF_1_const.png)
Okay, as expected, this in not really good hash function   
dispersion is 19990.00075009001
### 1.2 len
![HF2](/graphs/HF_2_len.png)
Looks like the first one. Let's scale it a bit
![HF2_sc](/graphs/HF_2_len_scaled.png)
Looks like normal distribution   
dispersion is 2162.595939368402. Better, but still too high
### 1.3 first ascii
![HF3](/graphs/HF_3_first_ascii.png)
Let's scale   
![HF3_sc](/graphs/HF_3_first_ascii_scaled.png)
dispersion is 1170.5983397284558.   
### 1.4 sum of ascii
![HF4](/graphs/HF_4_sum_ascii.png)
![HF4_sc](/graphs/HF_4_sum_ascii_scaled.png)
Wow! Looks pretty
My theory of this graph: one-len-words si the first little hill, the next hill - two-len words and further   
dispersion is 37.72660896884195, nice!
### 1.5 ror
![HF5](/graphs/HF_5_ror.png)
Much better than last functions, distributed on all 
dispersion is 12.867980174522803
### 1.6 rol
![HF6](/graphs/HF_6_rol.png)
Wow, it really differs from ror
dispersion is 4.34590186277604, still don't have ideas why they differs so much
### 1.7 crc32
![HF7](/graphs/HF_7_crc32.png)
Niice, maximum bucket size is 6   
dispersion is 0.9834975021219428   
So, this is the best hash function and I will use it
## 2. Real dictionary
New make target creates .out file that gets .txt file as input and creates .html file with same text, but when you toggle word with your mouse it shows it's translation
## 3. Speeding up
What I want is to speed up all of this. Let's test the time.   
Tolstoy's "War and peace" has about 200 000 words, so let's stranslate 20 of those books (4 000 000 words). Words are generated randomly chars from 0 to 128, length is random from 0 to 20.
### 3.1 testing
| O0     | O1     | O2     | O3     |
| ------ | ------ | ------ | ------ |
| 1,009s | 0,675s | 0,551s | 0,700s |

So, that's it.   
Let's see what callgrind says
![cg_o0](/callgrind_results/cg_o0.png)
This is callgrind of -O0
![cg_o1](/callgrind_results/cg_o1.ng)
Callgrind of -O1. Hash function became much faster
![cg_o2](/callgrind_results/cg_o2.png)
Callgrind of -O2
![cg_o3](/callgrind_results/cg_o3.png)
Callgrind of -O3


//here is line i completed true


### 3.2 analyzing
o1, o2, o3 doesn't really differ. Let's try to optimize some functions. I won't optimize functions such as DoTests or random that generates tests, i will only speed up functions that called while getting answer. The slowest is hash_funcions_crc32, next is LST_search and HT_Search.
* Hash function calls strlen, but let's see the chain: the argument is char* without length, DICT_GetTranslation calls HT_search with same char* without length HT computes hash using strlen, and then LST compares strings without length needed, so strlen stays here. Also, as we can see, strlen already speeded up with avx2.   
* Crc32 optimization: [there](https://github.com/komrad36/CRC) is a big article of speeding up crc32, i will take hardware optimization that uses _mm_crc32_u8, because we have too few length.
* HT_search: it needs to take mod prime number, o3 optimized it as much as it can
* Strcmp: strcmp avx2 source code consists of about 500 lines, so maybe we can do it faster
to count effectivenes, let's take sum of tacts and sub test genering, like for o3 it is 3 3645 335 - 1 173 847 - 966458620 - 509418811 - 210099700 = 785 510 618
### 3.2 rewriting
#### crc32 rewrite
![cg_o3_hf](/callgrind_results/cg_o3_hf.png)
hash function became better! now score is 637 832 025
and time is 0,640s versus no optimization 0,700.
#### word compare
![cg_o3_hf_strcmp](/callgrind_results/cg_o3_hf_strcmp.png)   
its better!
score is 548 153 850, and slow strcmp avx became fast 0x01bc
to talk about time, it is 0,596s versus last 0,640s versus no opt 0,700s
#### strlen
![cg_o3_hf_strcmp_strlen](/callgrind_results/cg_o3_hf_strcmp_strlen.png)   
Oh no! This is really bad. So, o3 knows how to count string length better than me
#### crc32 with asm 
Rewrite crc32 with asm, but there is fun fact: crc32(ABCD) = crc32(A^crc32(B^crc32(C^crc32(D)))), so if word len >= 8 we can use crc32 for uint64_t as 8 chars, speed x8!
![cg_o3_hfasm_strcmp](/callgrind_results/cg_o3_hfasm_strcmp.png)
the best result, it gives 0,582s in time, 492 451 173 in score
