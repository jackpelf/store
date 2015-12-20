#include<stdio.h>
int main()
{	
	char buf[40];
	char tmp[40];
	int n;
	int i,j,h;
	scanf("%d", &n);
	for (i = 0; i < n; i++)
	{
		scanf("%s", buf);
		for(j = 5; j <= 9; j++)
			putchar(buf[j]);
		putchar('/');
		for(j = 0; j <= 3; j++)
			putchar(buf[j]);
		putchar('-');
		tmp[0] = buf[11];
		tmp[1] = buf[12];
		tmp[2] = 0;
		h = atoi(tmp);
		if(h == 0)
		{
			putchar('1');
			putchar('2');
			printf("%sam",&buf[13]);
		}
		else if(h < 12)
		{	
			printf("%sam",&buf[11]);
		}
		else if(h == 12)
		{
			printf("%spm",&buf[11]);
		}
		else 
		{
			printf("%02d",h-12);
			printf("%spm",&buf[13]);
		}
		putchar('\n');
	}
	return 0;
}
