#include<stdio.h>
int buf[1000000];
int qs(int l, int r)
{
	if(l < r)
	{
		int key = buf[l];
		int low = l;
		int high = r;
		while(low < high)
		{
			while(low < high && buf[high] >= key)
			{
				high --;
			}
			buf[low] = buf[high];
			while(low < high && buf[low] <= key)
			{
				low++;	
			}
			buf[high] = buf[low];
		}
//		printf("low = high: %d\n", low);
		buf[low] = key;
		qs(l, low-1);
		qs(low+1, r);
	}
}


		
int main()
{
	int i = 0;
	int n = i;
	scanf("%d",&n);
	while(scanf("%d", &buf[i]) != EOF) i++;
	n = i;
	qs(0, n-1);

	int miss,more;

	for(i=1; i<n; i++)
	{
		if(buf[i-1] + 2 == buf[i])
			miss = buf[i] - 1;
		if(buf[i-1]  == buf[i])
			more = buf[i];
	}
	printf("%d %d\n", miss, more);	
	return 0;
}
