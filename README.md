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
This is callgrind of -O0.   
![cg_o1](/callgrind_results/cg_o1.png)
Callgrind of -O1.
![cg_o2](/callgrind_results/cg_o2.png)
Callgrind of -O2
![cg_o3](/callgrind_results/cg_o3.png)
Callgrind of -O3



### 3.2 analyzing
o2, o3 doesn't really differ. Let's try to optimize some functions. I won't optimize functions such as DoTests or random that generates tests, i will only speed up functions that called while getting answer. The slowest is hash_funcions_crc32, next is LST_search, strcmp and HT_Search.   
To see the difference i will compare time and tacts from callgrind
### 3.2 rewriting
#### crc32 rewrite
Okay, at first, there is an intel command called crc32. Secondly, I am rewriting it in asm. Thirdly, i am going to do a trick: if len of string is more than 8, i can take first 8 chars into uint64_t and call one crc32 instead of eight, answer will be the same.
![cg_o3_hf](/callgrind_results/cg_o3_hf.png)
woah! now hf does 6 times less tacts! What about time? 
0,422s! That's 40% faster! Les gooo further

//here is line i completed true
#### Lst_search rewrite
That function is second in the list. Rewriting it in asm. Here you should be careful with structures and their sizes
![cg_o3_hf_lstsrch](/callgrind_results/cg_o3_hf_lstsrch.png)
0,411s. I think hash table search function ate hash function. So, 41 % of time

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
