/*
raw
gcc -lcrypto md5.c
*/
#include<stdio.h>
#include<omp.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<openssl/md5.h>
char *res = "\x48\x50\xB7\x44\x6B\xBB\x20\xAA\xD1\x40\xE7\xB0\xA9\x64\xA5\x7D";
int md5(char *in)
{	
	int i;
	unsigned char out[16];
	MD5_CTX c;
	MD5_Init(&c);
	MD5_Update(&c, in, strlen(in));
	MD5_Final(out, &c);
	int flag = 1;
	for(i=0; i<16; i++)
	{
		if(res[i] != out[i]);
		{
			flag = 0;
			break;
		}
	}
	return flag;
}
int main()
{
	long long i = 0;
	char buf[100];
	time_t ts = time(0);
	#pragma omp parallel for
	for(i=1;i<0x100000001;i++)
	{
		long long tmp = 2453148193 + 0x100000000*i;
		sprintf(buf, "%ld\x00", tmp);
		int ans = atoi(buf);
		if(md5(buf))
		{
			puts(buf);
		}
	}
	time_t te = time(0);
	printf("time: %d\n",te - ts);
	return 0;
}

