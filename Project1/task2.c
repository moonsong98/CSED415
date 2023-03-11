// Task2: Given p, q, and e, find the private key d
#include <stdio.h>
#include <string.h>
#include <openssl/bn.h>

/**
 * Print Big Number w/ Hexadecimal Format
 * */
void printBN (BIGNUM * a) {
    char* number_str = BN_bn2hex(a);
    printf("%s", number_str); 
    OPENSSL_free(number_str);
}

int main () {
    BN_CTX *ctx = BN_CTX_new(); 
    char p_input[33], q_input[33], e_input[7];
    scanf("%s %s %s", p_input, q_input, e_input);

    // Initiate p, q, e, d, p_minus_1, q_minus_1
    BIGNUM *one = BN_new(); BN_hex2bn(&one, "1");
    BIGNUM *p = BN_new(); BN_hex2bn(&p, p_input);
    BIGNUM *p_minus_1 = BN_new(); BN_sub(p_minus_1, p, one);
    BIGNUM *q = BN_new(); BN_hex2bn(&q, q_input);
    BIGNUM *q_minus_1 = BN_new(); BN_sub(q_minus_1, q, one);
    BIGNUM *e = BN_new(); BN_hex2bn(&e, e_input);
    BIGNUM *d = BN_new(); 
    BIGNUM *totient = BN_new(); 

    // Calculate a totient function value & get a private key
    BN_mul(totient, p_minus_1, q_minus_1, ctx);
    BN_mod_inverse(d, e, totient, ctx);

    // Print a private key
    printBN(d);

    return 0;
}
