/*
raw
set keys, iv, input_data, len
set EN?DE
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/des.h>

DES_cblock Key1 = { 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11 };
DES_cblock Key2 = { 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22 };
DES_cblock Key3 = { 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33 };
DES_key_schedule SchKey1,SchKey2,SchKey3;
unsigned char input_data[] = "\xA7\x25\x02\x7F\xDD\x0B\x7F\x82\xF5\x52\xB0\x96\xAB\xF6\xAE\x8F\x4D\x8F\x81\x1C\xCC\xC3\x22\x64";
DES_cblock iv = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };



void print_data(const char *tittle, const void* data, int len);

#define EN 1
#define DE 0

void tdes(int choice)
{
	int len = strlen(input_data);
	unsigned char* text = malloc(len);
	DES_set_odd_parity(&iv);
	
	if ( -2 == (DES_set_key_checked(&Key1, &SchKey1) || DES_set_key_checked(&Key2, &SchKey2) || DES_set_key_checked(&Key3, &SchKey3)))
	{
		printf(" Weak key ....\n");
		exit(0);
	}

	if(choice == EN)
	{
		DES_ede3_cbc_encrypt( (unsigned char*)input_data, (unsigned char*)text, len, &SchKey1, &SchKey2, &SchKey3,&iv, DES_ENCRYPT);
		print_data("\n Encrypted", text, len);
	}
	else if(choice == DE)
	{
		memset(iv,0,sizeof(DES_cblock)); // You need to start with the same iv value
		DES_set_odd_parity(&iv);
		DES_ede3_cbc_encrypt( (unsigned char*)input_data, (unsigned char*)text, len, &SchKey1, &SchKey2, &SchKey3,&iv,DES_DECRYPT);
		print_data("\n Decrypted", text, len);
	}
}
void print_data(const char *tittle, const void* data, int len)
{
	printf("%s : ",tittle);
	const unsigned char * p = (const unsigned char*)data;
	int i = 0;
	
	for (; i<len;++i)
		printf("%02X", *p++);
	printf("%s : %s", tittle, data);
	
	printf("\n");
}
int main()
{
	tdes(DE);
	return 0;
}
