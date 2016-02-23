#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(int argc, char **argv)
{
	int buf[8];
	int captcha = atoi(argv[1]);
	time_t t = time(0) - 3;
	srand(t);
	for(int i=0; i<8; i++)
	{
		buf[i] = rand();
	}
	int tmp =  buf[1] + buf[2] - buf[3] + buf[4] + buf[5] - buf[6] + buf[7];
	int res = captcha - tmp;
	printf("%x\n", res);
	return 0;
}
