#include<stdio.h>
void vul();
int main()
{
	char buf[50];
	setbuf(stdout, NULL);
	setbuf(stdin, NULL);
	puts("welcome vul arm");
	read(0, buf, 0xfff);
	puts(buf);
	return 0;
}
void vul()
{
	execve("/bin/sh", NULL, NULL);
}
