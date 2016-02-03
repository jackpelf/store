#include<stdio.h>
int vul()
{
	system("sh");
}

int func()
{
	char buf[20];
	puts("hello pwm me");
	fflush(stdout);
	read(0, buf, 200);
	puts(buf);
	return 0;
}
int main()
{
	func();
	return 0;
}
