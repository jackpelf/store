#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define POLY 0xeff67c77d13835f7ULL;
unsigned long long table[256];
void init_table()
{
	int i,bit;
	for(i=0; i<256; i++)
	{
		unsigned long long c = i;
		for(bit = 0; bit<8; bit++)
		{
			if(c&1)
			{
				c = (c>>1) ^ POLY;
			}
			else
				c = c>>1;
		}
		table[i] = c;
	}
}
unsigned long long crc64(unsigned char *p,int len)
{
	char buf[100] = "\xda\x1d\xef\xbe\xad\xde\xad\xab";
	strncpy(&buf[8], p, len);
	unsigned long long crc = 0xffffffffffffffff;
	len = len + 8;
	printf("%d\n", len);
	while(len--)
	{
		crc = (crc >> 8) ^ (table[0xff & (crc^*p++)]);
	}
	return crc;
}
void hmac(unsigned long long key, unsigned char *p, int len)
{
	unsigned char buf[100];
	unsigned long long ti = 0x3636363636363636^ key;
	unsigned long long to = 0x5c5c5c5c5c5c5c5c ^ key;
	*(unsigned long long *)buf = ti;
	strncpy(&buf[8], p, len);
	*(unsigned long long *)(buf+8) = crc64(buf,len + 8);
	*(unsigned long long *)buf = to;
	printf("%016lx\n",crc64(buf,16));
}	
int main()
{
	unsigned char *p = "zupe zecret";
	init_table();
	printf("%016lx\n",crc64("\x08",1));
//	hmac(0, p, 0);
	return 0;
}
