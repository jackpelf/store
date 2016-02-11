/*
gcc -lcrypto
raw
set key,iv,plain_text
*/
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/aes.h>
 
int main(int argc, char** argv) {
    AES_KEY aes;
    unsigned char key[16];        // AES_BLOCK_SIZE = 16
    unsigned char iv[16];        // init vector
    unsigned char* plain_text;
    unsigned char* encrypt_string;
    unsigned int len;        // encrypt length (in multiple of AES_BLOCK_SIZE)
    unsigned int i;

    FILE *fp;
    fp = fopen("text", "rb");
    fseek(fp, 0, SEEK_SET);
    fseek(fp, 0, SEEK_END);
    int filelen = ftell(fp);
    plain_text = malloc(filelen + 16);
    read(fp, plain_text, filelen);

 
    // set the encryption length
    len = 0;
    if ((strlen(plain_text) + 1) % AES_BLOCK_SIZE == 0) {
        len = strlen(plain_text) + 1;
    } else {
        len = ((strlen(plain_text) + 1) / AES_BLOCK_SIZE + 1) * AES_BLOCK_SIZE;
    }
 
    // set the input string
    plain_text = (unsigned char*)calloc(len, sizeof(unsigned char));

 
    if (AES_set_encrypt_key(key, 128, &aes) < 0) {
        fprintf(stderr, "Unable to set encryption key in AES\n");
        exit(-1);
    }
 
    // alloc encrypt_string
    encrypt_string = (unsigned char*)calloc(len, sizeof(unsigned char));    
    if (encrypt_string == NULL) {
        fprintf(stderr, "Unable to allocate memory for encrypt_string\n");
        exit(-1);
    }
 
    // encrypt (iv will change)
    AES_cbc_encrypt(plain_text, encrypt_string, len, &aes, iv, AES_ENCRYPT);
 
 
    printf("encrypted string = ");
    for (i=0; i<len; ++i) {
        printf("%x%x", (encrypt_string[i] >> 4) & 0xf, 
                encrypt_string[i] & 0xf);    
    }
    printf("\n");
 
    return 0;
}
