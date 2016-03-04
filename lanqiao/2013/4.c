//9088
#include<stdio.h>
int main()
{
	int ri;
	int i;
	char buf[100];
	for(i=1000; i<9999; i++)
	{
		sprintf(buf,"%d", i);
		int k=0;
		int notw = 0;
		while(buf[k])
		{	
			switch(buf[k])
			{
				case '1':buf[100 - k] = '1';break;
				case '2':buf[100-k] = '5';break;
				case '5':buf[100-k] = '2';break;
				case '6':buf[100-k] = '9';break;
				case '9':buf[100-k] = '6';break;
				case '8':buf[100-k] = '8';break;
				case '0':buf[100-k] = '0';break;
				default:notw = 1;break;
			}
			k++;
		}
		if(buf[--k] == '0')
			notw = 1;
		if(!notw)
		{
			sscanf(buf+100-k,"%d", &ri);
			int rj;
			int j;
			for(j=1000; j<9999; j++)
			{
				sprintf(buf,"%d", j);
				int k=0;
				int notw = 0;
				while(buf[k])
				{	
					switch(buf[k])
					{
						case '1':buf[100-k] = '1';break;
						case '2':buf[100-k] = '5';break;
						case '5':buf[100-k] = '2';break;
						case '6':buf[100-k] = '9';break;
						case '9':buf[100-k] = '6';break;
						case '8':buf[100-k] = '8';break;
						case '0':buf[100-k] = '0';break;
						default:notw = 1;break;
					}
					k++;
				}
				if(buf[--k] == '0')
					notw = 1;
				if(!notw)
				{
					sscanf(buf+100-k,"%d", &rj);
//					printf("%d\n",ri+rj-i-j);
					if(ri+rj-i-j == 558)
					{	
						int tmp;
						tmp = abs(i - ri);
						if( (tmp > 200 && tmp < 300) || ( tmp>800 && tmp<900 ) )
						{
							tmp = abs(j - rj);
							if( (tmp > 200 && tmp < 300) || ( tmp>800 && tmp<900 ) )
							{
								if( ( (i-ri<0) && (j-rj>0) ) || ( (i-ri>0) && (j-rj<0)) )
									printf("i:%d, j:%d ri:%d rj:%d\n",i,j,ri,rj);
							}
						}
					}
				}
			}
		}
	}
	return 0;
}
