#include<stdio.h>
#include<string.h>
int main()
{
	int i,n;
	char buf0[20];
	char buf[220];
	while(1)
	{
		gets(buf0);
		if(!strcmp(buf0, "ENDOFINPUT"))	
			break;
		gets(buf);
		gets(buf0);
		n = strlen(buf);
		for(i=0; i<n; i++)
		{
			if(buf[i]<'A' || buf[i]>'Z')
				putchar(buf[i]);
			else
			{
				if(buf[i] < 'F')
					putchar('Z' -  (4 -  (buf[i] - 'A')));
				else
					putchar(buf[i] - 5);
			}
		}
		putchar('\n');
	}
}
