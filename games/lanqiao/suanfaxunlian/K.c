#include<stdio.h>
#include<stdlib.h>
int cmp(void *a, void *b)
{
	return *(int*)b-*(int*)a;
}
int main()
{
	int buf0[1000],buf1[1000];
	int n,m;
	int i,j;
	scanf("%d", &n);
	for(i=0; i<n; i++)
		scanf("%d", &buf0[i]);
	scanf("%d", &m);
	for(i=0; i<m; i++)
	{	
		int start, end, k;
		int c = 0;
		scanf("%d%d%d", &start, &end, &k);	
		for(j=start-1; j<end; j++)
			buf1[c++] = buf0[j];
		qsort(buf1, end-start+1, sizeof(int), cmp);
		printf("%d\n", buf1[k-1]);
	}
	return 0;
}
