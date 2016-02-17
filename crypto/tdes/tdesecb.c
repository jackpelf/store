/*
gcc tdesecb.c -lcrypto
raw 
set input_data, len, keys
set EN?DE
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/des.h>
void print_data(const char *tittle, const void* data, int len);
void tdes(int choice);

DES_key_schedule SchKey1,SchKey2,SchKey3;


#define EN 1
#define DE 0
int main()
{
	tdes(EN);
	return 0;
}
void tdes(int choice)
{
	unsigned char input_data[100] = "iamflag";
	int len = strlen(input_data);
	DES_cblock Key1 = { 0, 0, 0, 0, 0, 0, 0, 0 };
	DES_cblock Key2 = { 0, 0, 0, 0, 0, 0, 0, 0 };
	DES_cblock Key3 = { 0, 0, 0, 0, 0, 0, 0, 0 };
	unsigned char *text = malloc(len);


	
	if ( -2 == (DES_set_key_checked(&Key1, &SchKey1) || DES_set_key_checked(&Key2, &SchKey2) || DES_set_key_checked(&Key3, &SchKey3)))
	{
		printf(" Weak key ....\n");
		exit(0);
	}

	if(choice == EN)
	{
		int i;
		for(i=0; i<len + 4; i += 8)
		{
			DES_ecb3_encrypt( (C_Block *)(input_data + i), (C_Block *)(text + i), &SchKey1, &SchKey2, &SchKey3, DES_ENCRYPT);
		}
		print_data("\n Encrypted",text,8*((len + 4) / 8));
	}
	else if(choice == DE)
	{
		int i;
		for(i=0; i<len + 4; i += 8)
		{
			DES_ecb3_encrypt( (C_Block *)(input_data + i), (C_Block *)(text + i), &SchKey1, &SchKey2, &SchKey3, DES_DECRYPT);
		}
		print_data("\n Decrypted",text,8*((len + 4) / 8));
	}
}
void print_data(const char *tittle, const void* data, int len)
{
	printf("%s : ",tittle);
	const unsigned char * p = (const unsigned char*)data;
	int i = 0;
	
	for (; i<len;++i)
		printf("\\x%02X", *p++);
	printf("%s : %s", tittle, data);
	
	printf("\n");
}
