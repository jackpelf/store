/*
raw
gcc -lcrypto sha1.c
*/

#include<openssl/sha.h>
#include<stdio.h>
#include<string.h>
void sha512()
{
	int i;
	char in[20] = "ISGISG";
	unsigned char out[64];
	SHA512_CTX c;
	SHA512_Init(&c);
	SHA512_Update(&c, in, strlen(in));
	SHA512_Final(out, &c);
	for(i=0; i<64; i++)
		printf("%02x", out[i]);
	puts("");
}
void sha384()
{
	int i;
	char in[20] = "ISGISG";
	unsigned char out[48];
	SHA512_CTX c;
	SHA384_Init(&c);
	SHA384_Update(&c, in, strlen(in));
	SHA384_Final(out, &c);
	for(i=0; i<48; i++)
		printf("%02x", out[i]);
	puts("");
}
void sha256()
{
	int i;
	char in[20] = "ISGISG";
	unsigned char out[32];
	SHA256_CTX c;
	SHA256_Init(&c);
	SHA256_Update(&c, in, strlen(in));
	SHA256_Final(out, &c);
	for(i=0; i<32; i++)
		printf("%02x", out[i]);
	puts("");
}
void sha224()
{
	int i;
	char in[20] = "ISGISG";
	unsigned char out[28];
	SHA256_CTX c;
	SHA224_Init(&c);
	SHA224_Update(&c, in, strlen(in));
	SHA224_Final(out, &c);
	for(i=0; i<28; i++)
		printf("%02x", out[i]);
	puts("");
}
void sha1()
{
	int i;
	char in[20] = "ISGISG";
	unsigned char out[20];
	SHA_CTX c;
	SHA1_Init(&c);
	SHA1_Update(&c, in, strlen(in));
	SHA1_Final(out, &c);
	for(i=0; i<20; i++)
		printf("%02x", out[i]);
	puts("");
}
int main()
{
	sha1();
	sha224();
	sha256();
	sha384();
	sha512();
	return 0;
}
