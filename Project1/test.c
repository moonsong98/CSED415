#include<stdio.h>
#include<openssl/bn.h>

int main(void) {
    char m_input[4] = "888"; 
    char p_input[33];
    char q_input[33];
    char e_input[7];
    char d_input[100];
    scanf("%s %s %s %s", p_input, q_input, e_input, d_input);
    printf("p: %s\nq: %s\ne: %s\nd: %s\nOriginal Message: %s\n", p_input, q_input, e_input, d_input, m_input);

    BN_CTX* ctx = BN_CTX_new();
    BIGNUM* p = BN_new(); BN_hex2bn(&p, p_input);
    BIGNUM* q = BN_new(); BN_hex2bn(&q, q_input);
    BIGNUM* e = BN_new(); BN_hex2bn(&e, e_input);
    BIGNUM* d = BN_new(); BN_hex2bn(&d, d_input);
    BIGNUM* m = BN_new(); BN_hex2bn(&m, m_input);
    BIGNUM* n = BN_new(); 
    BIGNUM* c = BN_new();
    BIGNUM* result = BN_new();

    BN_mul(n, p, q, ctx);
    BN_mod_exp(c, m, e, n, ctx);
    printf("Encrypted Message: %s\n", BN_bn2hex(c));
    BN_mod_exp(result, c, d, n, ctx);

    char* number_str = BN_bn2hex(result);
    printf("Decrypted Message: %s\n", number_str);
    OPENSSL_free(result);
}
