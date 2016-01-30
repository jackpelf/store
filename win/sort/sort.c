#include<stdio.h>
#include<stdlib.h>
#include<math.h>


long long int cmp;
long long int mov;
int tmp[200000];
int is_all;
long long int mem[10][4];


typedef struct
{
	int length;
	int data[200000];
}SqList;

void generate(SqList *L)  
{
	int i,n;
	int r;
	if(is_all == 0)
	{
		puts("input how many data:");
		scanf("%d", &n);
	}
	else
		n = is_all;
	srand((unsigned)time(NULL));
	L->length = n;
	for (i = 1; i<=n; i++)
	{
		r = rand();
		L->data[i] = r;
	}
}
void print(SqList *L)    
{
	int i;
	char c;
	if( !is_all)
	{
		puts("print the Sqlist? <Y/N>");
		scanf("%c", &c);
		scanf("%c", &c);
		if(c == 'y' || c == 'Y')
		{
		puts("now the SqList looks like");
		for(i=1 ; i<L->length; i++)
			printf("%d\n", L->data[i]);
		}	
		else if(c == 'n' || c == 'N')
			;
		else
			puts("invalid input");
	}

}

void reverse(SqList *L)
{
	int n = L->length;
	int i;
	int tmp;
	for(i = 1; i<n/2; i++)
	{	
		tmp = L->data[i];
		L->data[i] = L->data[n+1-i];
		L->data[n+1-i] = tmp;
	}
}	


//-------------------------bubble-----------------------
void BubbleSort(SqList *L)
{
	int i,j;
	int tmp;
	char c;
	puts("\nBubble sorting");
	if( is_all == 0 )
	{
		puts("generating a sqlist");
		generate(L);
		puts("done");
	}
	puts("sorting");
	mov = 0; cmp = 0;
	for (i=1; i<=L->length; i++)
	{
		for( j = L->length; j > i; j--)
		{
			if(L->data[j-1] > L->data[j] )
			{
				cmp ++;
				tmp = L->data[j-1];
				L->data[j-1] = L ->data[j];
				L->data[j] = tmp;
				mov += 3;
			}
		}
	}
	puts("done");
	printf("total compare :%lld, total move :%lld\n", cmp, mov);
	print(L);
}
//-----------------------Quicksort------------------------
int Partition(SqList *L, int a_low, int a_high)
{
	int pivotkey;
	int low = a_low,high = a_high;
	L->data[0] = L->data[low];
	mov ++;
	pivotkey = L->data[low];
	mov ++;
	while(low<high)
	{
		while(low<high && L->data[high] >= pivotkey) --high;
		cmp ++;
		L->data[low] = L->data[high];
		mov ++;
		while(low<high && L->data[low] <= pivotkey) ++low;
		cmp ++;
		L->data[high] = L->data[low];
		mov ++;
	}
	L->data[low] = L->data[0];
	mov ++;
	return low;
}

void QSort(SqList *L, int low, int high)
{
	int pivotloc;
	if(low < high)
	{
		pivotloc = Partition(L, low, high);
		mov++;
		QSort(L, low, pivotloc - 1);
		QSort(L, pivotloc + 1, high);
	}
}

void QuickSort(SqList *L)
{
	char c;
	puts("\nQuick sorting");
	if( is_all == 0 )
	{
		puts("generating a sqlist");
		generate(L);
		puts("done");
	}
	puts("sorting");
	cmp = 0; mov = 0;
	QSort(L, 1, L->length);
	puts("done");
	printf("total compare :%lld, total move :%lld\n", cmp, mov);
	print(L);
}
//--------------------insertsort----------------------
void InsertSort(SqList *L)
{
	char c;
	cmp = 0; mov = 0;
	puts("\ninsert sorting");
	puts("sorting");
	int i,j;
	for (i=2; i<=L->length; i++)
	{
		if(L->data[i]<L->data[i - 1])
		{
			L->data[0] = L->data[i];
			L->data[i] = L->data[i-1];  //move_last
			mov += 2;
			for ( j = i - 2; L->data[0] < L->data[j]; j--)
			{
				cmp++;
				L->data[j+1] = L->data[j];
				mov++;
			}
			L->data[j+1] = L->data[0];
			mov++;
		}
	}
	puts("done");
	printf("total compare :%lld, total move :%lld\n", cmp, mov);
	print(L);
}

//---------------------select sorting-----------------------

void SelectSort(SqList *L)
{
	char c;
	cmp = 0; mov = 0;
	puts("\nselect sorting");
	if( is_all == 0 )
	{
		puts("generating a sqlist");
		generate(L);
		puts("done");
	}
	puts("sorting");
	int i,j;
	for (i=1; i<=L->length; i++)
	{
		int s_i = i;
		for(j = i+1; j <= L->length; j++)      //select min
		{
			if(L->data[s_i] > L->data[j] )
			{
				int tmp = L->data[i];
				L->data[i] = L->data[s_i];
				L->data[s_i] = tmp;
				cmp++;
				mov +=3;
			}
		}
	}
	puts("done");
	printf("total compare :%lld, total move :%lld\n", cmp, mov);
	print(L);
}

//--------------------------shell sorting------------------
void shellinsert(SqList *L, int dk)
{
	int i,j;
	for( i= dk +1; i<=L->length; i++)
	{
		if(L->data[i] < L->data[i-dk])
		{
			cmp++;
			L->data[0] = L->data[i];
			mov++;
			for( j = i-dk; j>0 && L->data[0] <  L->data[j]; j-=dk)
			{	
				cmp ++;
				L->data[j+dk] = L->data[j];
				mov++;
			}
			L->data[j+dk] = L->data[0];
			mov++;
		}
	}
}
void shellSort(SqList *L)
{
	int t = log(110000)/log(2);
	int dlta[50];
	int i,k;
	char c;
	cmp = 0; mov = 0;
	for (i = 0; i< t; i++)
		dlta[i] = pow(2, t - i) + 1;
	puts("\nshell sorting");
	if( is_all == 0 )
	{
		puts("generating a sqlist");
		generate(L);
		puts("done");
	}
	puts("sorting");
	for(k = 0; k<t; k++)
	{
		shellinsert(L,dlta[k]);
	}	
	puts("done");
	printf("total compare :%lld, total move :%lld\n", cmp, mov);
	print(L);
}

//---------------------heap sort-------------------------------

void HeapAdjust(SqList *L, int s, int m)
{
	int rc,j;
	rc = L->data[s];
	mov++;
	for( j = 2*s; j<=m; j*=2)
	{
		if(j<m && L->data[j] < L->data[j+1] ) ++j;
		cmp ++;
		if( rc > L->data[j] ) break;
		cmp ++;
		L->data[s] = L->data[j]; s = j;
		mov++;
	}
	L->data[s] = rc;
	cmp++;
}


void HeapSort(SqList *L)
{
	int i;
	char c;
	cmp = 0; mov = 0;
	puts("done");
	puts("\nheap sorting");
	if( is_all == 0 )
	{
		puts("generating a sqlist");
		generate(L);
		puts("done");
	}
	puts("sorting");
	for( i = L->length/2; i>0; i--)
		HeapAdjust(L, i , L->length);
	for( i = L->length; i>1; i--)
	{
		int tmp = L->data[1];
		L->data[1] = L->data[i];
		L->data[i] = tmp;
		mov += 3;
		HeapAdjust(L, 1, i-1);
	}
	puts("done");
	printf("total compare :%lld, total move :%lld\n", cmp, mov);
	print(L);
}

//----------------------------------------merge---------------------------------------

void Merge(int *array, int i, int m, int n)
{
	int j,k,l;
	l = i;
	for( j = m+1, k = i;l<=m && j<=n; k++)
	{
		if(array[l] < array[j])
		{	
			tmp[k] = array[l++];
		}
		else
		{
			tmp[k] = array[j++];
		}
		cmp++;
		mov++;
	}
	while( l<= m)
	{
		tmp[k] = array[l++];
		k++;
		mov++;
	}
	while( j<= n)
	{
		tmp[k] = array[j++];
		k++;
		mov++;
	}
	for(l=i; l<=n; l++)
	{
		array[l] = tmp[l];
		cmp++;
		mov++;
	}
}

void MSort(int *array, int s, int t)
{
	int m;
	if(s == t)
	{
		;
	}
	else
	{
		m = (s+t)/2;
		MSort(array, s, m);
		MSort(array, m+1, t);
		Merge(array, s, m, t);
	}
}

void MergeSort(SqList *L)
{
	char c;
	cmp = 0; mov = 0;
	puts("\nMerge sorting");
	if( is_all == 0 )
	{
		puts("generating a sqlist");
		generate(L);
		puts("done");
	}
	puts("sorting");
	MSort(L->data, 1, L->length);
	puts("done");
	printf("total compare :%lld, total move :%lld\n", cmp, mov);
	print(L);
}

//---------------------------------BInsertSort------------------------------

void BInsertSort( SqList *L)
{
	int i,j,m,high,low;
	char c;
	cmp = 0; mov = 0;
	puts("\nBInsert sorting");
	if( is_all == 0 )
	{
		puts("generating a sqlist");
		generate(L);
		puts("done");
	}
	puts("sorting");
	for(i=2; i<=L->length; i++)
	{
		L->data[0] = L->data[i];
		mov++;
		low = 1;
		high = i-1;
		while(low <= high)
		{
			m = (low + high)/2;
			if(L->data[0] < L->data[m])
				high = m-1;
			else
				low = m + 1;
			cmp++;
		}
		for( j = i-1; j>=high+1; j--)
		{
			L->data[j+1] = L->data[j];
			mov++;
		}
		L->data[high+1] = L->data[0];
		mov++;
	}
	puts("done");
	printf("total compare :%lld, total move :%lld\n", cmp, mov);
	print(L);
}
//-----------------------------Path2Insert ----------------------------------
void Path2Insert (SqList *L)
{
	int i,k;
	char c;
	cmp = 0; mov = 0;
	puts("\nPath2Insert sorting");
	if( is_all == 0 )
	{
		puts("generating a sqlist");
		generate(L);
		puts("done");
	}
	int length = L->length - 1;
	int d[length];
	puts("sorting");
	
	int final = 0;
	int first = 0;

	int temp[length];

	temp[0] = L->data[0];
	for (i = 1; i <= length;i++)
	{
		if(L->data[i] > temp[final])
		{
			cmp++;
			final++;
			temp[final] = L->data[i];
			mov++;
		}
		if(L->data[i]< temp[first])
		{
			cmp++;
			first = (first-1+length)%length;
			temp[first] = L->data[i];
			mov++;
		}
		if(L->data[i] < temp[final]&&L->data[i] > temp[first])
		{
			cmp++;
			cmp++;
			int j = final++;
			while (L->data[i] < temp[j])
			{
				cmp++;
				temp[(j+1)%length] = temp[j];
				j = (j-1+length)%length;
				mov++;
			}
			temp[j+1] = L->data[i];
			mov++;
		}
	}
	for (k = 0; k < length; k++)
	{
		mov++;
		L->data[k+1] = temp[(first++)%length];
	}
	puts("done");
	printf("total compare :%lld, total move :%lld\n", cmp, mov);
	print(L);
}

//------------------------Radix----------------------------
int maxbit(int data[],int n) 
{  
	int d = 1;   
	int p =10;  
	int i;
	
	for(i = 0;i < n; ++i)  
	{  
		while(data[i] >= p)  
		{  
			cmp++;
			p *= 10;  
			++d;  
		}  
	}  
	return d;  
}  
void radixsort(SqList *L)
{ 
	puts("\nRadix sorting");
	if( is_all == 0 )
	{
		puts("generating a sqlist");
		generate(L);
		puts("done");
	}
	int n = L->length; 
	int *data = L->data;
	int d = maxbit(data,n);  
	int tmp[n];  
	int count[10];
	int i,j,k;  
	int radix = 1;  
	char c;
	cmp = 0; mov = 0;
	puts("sorting");
	for(i = 1; i<= d;i++)
	{  
		for(j = 0;j < 10;j++)  //clear count
		    	count[j] = 0; 
		for(j = 0;j < n; j++)  //write count
		{  
			k = (data[j]/radix)%10; 
			count[k]++;  
		}  
		for(j = 1;j < 10;j++)  
			count[j] = count[j-1] + count[j]; 
		for(j = n-1;j >= 0;j--)
		{  
			k = (data[j]/radix)%10;  
			tmp[count[k]-1] = data[j]; 
			mov++; 
			count[k]--;  
		}  
		for(j = 0;j < n;j++)       //copy to data 
		{
			data[j] = tmp[j];  
			mov++;
		}
		radix = radix*10;  
	}  
	puts("done");
	printf("total compare :%lld, total move :%lld\n", cmp, mov);
	print(L);
}  

void All(SqList *L)
{
	int n;
	int i=0;
	SqList *t=(SqList *)malloc(sizeof(SqList));
	puts("generating a sqlist");
	puts("input how many data:");
	scanf("%d", &is_all);
	generate(L);
	puts("done");
	*t=*L;

	int sig = 2;
	while(sig !=0)
	{	
		i = 0;
		int j = 0;
		if(sig == 1)
		{
			reverse(L);
			*t = *L;
			j = 2;
		}
		while(i != 10)
		{	
			if(i == 0)
				BubbleSort(L);
			if(i == 1)
				QuickSort(L);
			if(i == 2)
				InsertSort(L);
			if(i == 3)
				SelectSort(L);
			if(i == 4)
				shellSort(L);
			if(i == 5)
				HeapSort(L);
			if(i == 6)
				MergeSort(L);
			if(i == 7)
				BInsertSort(L);
			if(i == 8)
				Path2Insert(L);
			if(i == 9)
				radixsort(L);
			mem[i][0 + j] = cmp;
			mem[i][1 + j]=mov;
			i++;
			*L=*t;
		}			
		sig --;
	}                      
	i = 0;
	printf("\nThe result is:          compare        move       compare        move\n");
	printf("		      ����			����\n");
	printf("BubbleSortð��     %10lld    %10lld    %10lld    %10lld    \n", mem[i][0], mem[i][1], mem[i][2], mem[i][3]);
	i++;                                                                                                              
	printf("QuickSort����      %10lld    %10lld    %10lld    %10lld    \n", mem[i][0], mem[i][1], mem[i][2], mem[i][3]); 
	i++;                                                                                                              
	printf("InsertSortֱ�Ӳ��� %10lld    %10lld    %10lld    %10lld    \n", mem[i][0], mem[i][1], mem[i][2], mem[i][3]); 
	i++;                                                                                                              
	printf("SelectSortѡ��     %10lld    %10lld    %10lld    %10lld    \n", mem[i][0], mem[i][1], mem[i][2], mem[i][3]); 
	i++;                                                                                                              
	printf("ShellSortϣ��      %10lld    %10lld    %10lld    %10lld    \n", mem[i][0], mem[i][1], mem[i][2], mem[i][3]); 
	i++;                                                                                                              
	printf("HeapSort��         %10lld    %10lld    %10lld    %10lld    \n", mem[i][0], mem[i][1], mem[i][2], mem[i][3]); 
	i++;                                                                                                              
	printf("MergeSort�鲢      %10lld    %10lld    %10lld    %10lld    \n", mem[i][0], mem[i][1], mem[i][2], mem[i][3]); 
	i++;                                                                                                              
	printf("BInsertSort�۰����%10lld    %10lld    %10lld    %10lld    \n", mem[i][0], mem[i][1], mem[i][2], mem[i][3]); 
	i++;                                                                                                              
	printf("Path2Insert2·���� %10lld    %10lld    %10lld    %10lld    \n", mem[i][0], mem[i][1], mem[i][2], mem[i][3]); 
	i++;                                                                                                              
	printf(".RadixSort����     %10lld    %10lld    %10lld    %10lld    \n", mem[i][0], mem[i][1], mem[i][2], mem[i][3]); 
	i++;             
	is_all = 0;                   
}                                            





	

int main()
{
	SqList L;
	int chose;
	int i;
	is_all = 0;
	puts("\n----welcome to sorting system----");
	while(1)
	{
		puts("\n\nYour can chose: \n\
	1.ALL\n\
	2.BubbleSort\n\
	3.QuickSort\n\
	4.InsertSort\n\
	5.SelectSort\n\
	6.ShellSort\n\
	7.HeapSort\n\
	8.MergeSort\n\
	9.BInsertSort\n\
	10.Path2Insert\n\
	11.RadixSort\n\
	12.exit\n");
		scanf("%d", &chose);
		if(chose == 1 )
			All(&L);
		else if(chose == 2)
			BubbleSort(&L);
		else if(chose == 3)
			QuickSort(&L);
		else if(chose == 4)
			InsertSort(&L);
		else if(chose == 5)
			SelectSort(&L);
		else if(chose == 6)
			shellSort(&L);
		else if(chose == 7)
			HeapSort(&L);
		else if(chose == 8)
			MergeSort(&L);
		else if(chose == 9)
			BInsertSort(&L);
		else if(chose == 10)
			Path2Insert(&L);
		else if(chose == 11)
			radixsort(&L);
		else if(chose == 12)
			exit(0);
		else
			puts("invalid input");
	}
}