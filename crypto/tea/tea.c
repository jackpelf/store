#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void en(unsigned int n, unsigned char p[8], unsigned char k[16], unsigned char *c)
{
	int i;
	unsigned int v0,v1,sum = 0;
	unsigned int key[4];
	unsigned int delta=0x9e3779b9;
	v0 = *(unsigned int*)p;
	v1 = *(unsigned int*)(p+4);
	key[0] = *(unsigned int*)k;
	key[1] = *(unsigned int*)(k+4);
	key[2] = *(unsigned int*)(k+8);
	key[3] = *(unsigned int*)(k+12);
	for(i=0; i<n; i++)
	{
		sum += delta;
		v0 += ((v1 << 4) + key[0]) ^ (v1 + sum) ^ ((v1>>5) + key[1]);
		v1 += ((v0 << 4) ^ key[2]) ^ (v0 + sum) ^ ((v0>>5) + key[3]);
	}
	*(unsigned int*)c = v0;
	*(unsigned int*)(c + 4) = v1;
}	
void de(unsigned int n, unsigned char p[8], unsigned char k[16], unsigned char *c)
{
	int i;
	unsigned int delta=0x9e3779b9;
	unsigned int v0,v1,sum = 0xc6ef3720;
	unsigned int key[4];
	v0 = *(unsigned int*)c;
	v1 = *(unsigned int*)(c+4);
	key[0] = *(unsigned int*)k;
	key[1] = *(unsigned int*)(k+4);
	key[2] = *(unsigned int*)(k+8);
	key[3] = *(unsigned int*)(k+12);
	for(i=0; i<n; i++)
	{
		v1 -= ((v0 << 4) ^ key[2]) ^ (v0 + sum) ^ ((v0>>5) + key[3]);
		v0 -= ((v1 << 4) + key[0]) ^ (v1 + sum) ^ ((v1>>5) + key[1]);
		sum -= delta;
	}
	*(unsigned int*)p = v0;
	*(unsigned int*)(p + 4) = v1;
}	
int main()
{
	unsigned char key[16] = "thisisthekeyxtea";
	unsigned char p[9] = "plaintex";
	unsigned char c[9];
	en(32, p, key, c);
	puts(c);
	de(32, p, key, c);
	puts(p);
	return 0;
}
