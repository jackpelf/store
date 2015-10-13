#include<stdio.h>

__attribute__((constructor)) int hello()
{
	printf("hello elf\n");
}
int main()
{
	puts("i am main func");
}
