#include<stdio.h>
int main()
{
	int i,j,k,l,m,n,o,p;
	char x[] = "c678d6g64307gf4g`b263473ge35b5`9";
	char s[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!#$%&()*+,-./:;<=>?@[\\]^_`{|}~";
	puts(x);
	puts(s);
	unsigned char buf[9] = {0};
	for(i=0; i<strlen(s); i++)
	for(j=0; j<strlen(s); j++)
	for(k=0; k<strlen(s); k++)
	for(l=0; l<strlen(s); l++)
	for(m=0; m<strlen(s); m++)
	for(n=0; n<strlen(s); n++)
	for(o=0; o<strlen(s); o++)
	for(p=0; p<strlen(s); p++)
	{
		buf[0] = s[i] ^ x[0];//
		buf[1] = s[j] ^ x[1];//
		buf[2] = s[k] ^ x[2];//
		buf[3] = s[l] ^ x[3];//
		buf[4] = s[m] ^ x[4];//
		buf[5] = s[n] ^ x[5];//
		buf[6] = s[o] ^ x[6];//
		buf[7] = s[p] ^ x[7];//
		int tmp;
		unsigned char ans = 0;
		for (tmp = 0; tmp<8; tmp++)
		{
			ans = ans * 2 + buf[tmp];
		}
		printf("%d\n", ans);
	}
	
	return 0;
}
