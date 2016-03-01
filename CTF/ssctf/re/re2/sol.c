#include<stdio.h>
int main()
{
	unsigned char bf0,bf1,bf2,bf3;
	for(bf0 = 0; bf0<255; bf0++)
	{
		 bf1 = bf0 ^ 0x11;
		 bf3 = bf0 ^ 0x9;
		 bf2 = bf0 ^ 0x7e;
		unsigned tmp = (bf0 + bf1 + bf2 + bf3);
		if((tmp) == 0xdc)
		{
			printf("%d %d %d %d\t\t\t", bf0, bf1, bf2, bf3);
			 unsigned char stack0 = bf3 ^ 0x6f;
			 unsigned char stack1 = bf0 ^ 0x66;
			 unsigned char stack2 = bf2 ^ bf1 ^ 0x77 ^ bf3 ^ 0x6f ^ 0x18;
			 unsigned char stack3 = bf1 ^ 0x77 ^ bf3 ^ 0x6f ^ bf1 ^ 0x77;
			 unsigned int edx = (stack1 + stack2 + stack0 + stack3) >> 2;
			printf("%d\n", edx);
		}
	}
	return 0;
}
