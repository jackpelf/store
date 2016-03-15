#include<stdio.h>
int main()
{
	int i=2333;
	char *s="ANS:%d";
	puts("test");
	__asm
	{
		PUSH EAX
		MOV EAX,i
		PUSH EAX
		MOV EAX,s
		PUSH EAX
		CALL printf
		POP EAX
	}
	return 0;
}