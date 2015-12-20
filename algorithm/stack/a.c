#include<stdio.h>
#include<string.h>


int main()
{
	int n,i,count;
	char buf[10000];
	while(gets(buf))
	{
		n = strlen(buf);
		count = 0;
		for(i=0; i<n; i++)
		{	
			if(buf[i] == '(')
				count++;
			else if(buf[i] == ')')
				count--;
			else if(buf[i] == 'B')
				break;
		}
		printf("%d\n", count);
	}
	return 0;
}
