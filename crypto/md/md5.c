/*
raw
gcc -lcrypto md5.c
*/
#include<stdio.h>
#include<string.h>
#include<openssl/md5.h>

void md5()
{	
	int i;
	char in[20] = "ISGISG";
	unsigned char out[16];
	MD5_CTX c;
	MD5_Init(&c);
	MD5_Update(&c, in, strlen(in));
	MD5_Final(out, &c);
	puts("md5-32:");
	for(i=0; i<16; i++)
		printf("%02x", out[i]);
	puts("");
	puts("md5-16:");
	for(i=4; i<12; i++)
		printf("%02x", out[i]);
	puts("");
}
int main()
{
	md5();
	return 0;
}

