# Task 2

## Task
Given two prime numbers p, q, and public key e, goal of the task is to retrieve private key d.  

### Formula
$n = p * q$  
$\phi(n) = (p - 1) * (q - 1)$  
$\text{Choose } e \text{ which is relatively prime to } \phi(n) \text{ and }1 < e < \phi(n)$.

$\text{Get } d \text{ s.t. } (e*d) \equiv 1 \text{ } mod \text{ } \phi(n)$

## Commmand

```
gcc task2.c -lcrpyto
./a.out < input > privatekey
```

### For Test
```
gcc test.c -lcrypto
cat input privatekey | ./a.out
```

