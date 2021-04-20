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
| O0     | O1     | O2     | O3     |
| ------ | ------ | ------ | ------ |
| 0,854s | 0,765s | 0,729s | 0,709s |

So, that's it.   
Let's see what callgrind says