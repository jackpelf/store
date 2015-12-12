#include<stdio.h>
#include<stdlib.h>
char bss[200];
int main()
{
	char *p;
	int i;
	
	puts("\nmalloc 0");
	p = malloc(0);
	printf("%p\n", p);
	
	puts("\nmalloc 4");
	p = malloc(4);
	printf("%p\n", p);
	
	puts("\nmalloc 64");
	p = malloc(64);
	printf("%p\n", p);
	
	puts("\nmalloc 128");
	p = malloc(128);
	printf("%p\n", p);
	
	puts("\nmalloc 0x128k - 1");
	p = malloc(128 * 1024 - 1);
	printf("%p\n", p);
	
	puts("\nmalloc 4");
	p = malloc(4);
	printf("%p\n", p);
	
	puts("\nmalloc 0x128k ");
	p = malloc(128 * 1024);
	printf("%p\n", p);
	
	puts("\nmalloc 0x128k + 1");
	p = malloc(128 * 1024 + 1);
	printf("%p\n", p);
	
	sleep(23333);
}
