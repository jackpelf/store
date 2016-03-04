#include<stdio.h>
#include<unistd.h>
int main()
{
	pid_t pid = fork();
	char buf[100];
	if(pid == 0)
	{
		puts("i am child");
		puts("before setsid");
		sleep(5);
		gets(buf);
		setsid();
		puts("after setsid");
		sleep(11111110);
	}
	else if(pid > 0)
	{
		puts("i am parent");
		puts("parent exit");
		sleep(11111110);
	}
	return 0;
}
