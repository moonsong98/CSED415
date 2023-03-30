# Project 2

## Goal

Make a proactive password checker via implementing bloom filter.
Bloom filter consists of N(=3) hash functions and each hash function
results $\log_{2}K(=8192)$ bit number.

## Hash function

Since there are various hash functions like md5, sha1,
I had to choose one regarding accuracy and speed.
It is well known that speed of MurmurHash3 is faster than md5 or sha1,
but still robust. It fits to the requirement of bloom filter.  
Probability of false positive of bloom filter is $p = (1 - e^{-kn/m})^k$.  
As given in project instruction, n is 1380, m is 8192, and k is 3.
By calculation, we can get that p is 0.062438.
By the test I've done, implementing using Murmurhash3 satisfies the accuracy.

## How to run

It needs 4 arguments:

- -\-dict "file path of dictionary file"
- -\-cand "file path of test candidates file"
- -\-k "number of hash functions"
- -\-n "number of hash functions' result"

### Example

``` terminal
./checker --dict ./dictionary.txt --cand ./test_candidate.txt
```

The result would be saved in **Bloomchecked.txt** in same directory as ./checker

## Implementation

I installed mmh3 package which wraps MurmurHash3.
Since the result of mmh3 is 32 bit number, I used mmh3 % K for creating a map.
Seeds for mmh3 are chosen randomly.

## Test

I created a candidate generator via **candidate_generator.py**.
This file generates all possible words of which length is between 3 and 6,
which is same as words length of a dictionary.

### Result

![test\_result](https://user-images.githubusercontent.com/37493475/227563840-b5043a50-027e-4c3b-bd91-216bf36c0703.png)
As result shown above, seed with 14, 63, 26 which are chosen randomly,
probability of false positive is 0.062485,
which is close to the one I calculated above.
