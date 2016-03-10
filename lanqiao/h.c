#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
	int n;
	scanf("%d", &n);	
	int l = 3+2*n;
	char m[1000][1000];
	int i,j;
	memset(m, 0, sizeof(m));
	m[1][1] = '.';
	for(i=2; i<=l; i++)
	{
		if( i == 1 )	
			puts(".");
		else if( i%2 == 1 )
		{
			for(j=0; j<(i/2-1); j++)
			{
				m[i][1+2*j] = '$';
				m[i][2+2*j] = '.';
			}
			m[i][1+2*j] = '$';
			m[i][2+2*j] = '$';
			m[i][3+2*j] = '$';
		}
		else
		{
			for(j=0; j<(i/2-1); j++)
			{
				m[i][1+2*j] = '$';
				m[i][2+2*j] = '.';
			}
			m[i][1+2*j] = '.';
			m[i][2+2*j] = '.';
		}
	}
	for(i=1; i<=l; i++)
	{
		for(j=1; j<=i; j++)
		{
			m[j][i] =  m[i][j];
		}
	}
	for(i=1; i<=l; i++)
	{
		for(j=1; j<=l; j++)
		{
			m[i][2*l - j] =  m[i][j];
		}
	}
	for(i=1; i<=l; i++)
	{
		for(j=1; j<=2*l; j++)
		{
			m[2*l - i][j] =  m[i][j];
		}
	}
	for(i=1; i<=2*l - 1; i++)
	{
		puts(m[i] + 1);
	}
			
	return 0;
}
