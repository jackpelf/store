fchart chart;
hmlist m_list;
char nametmp[30]="_____";

LPVOID find_f(char* funcname)
{
	int i;
	LPVOID pf=NULL;
	for(i=0; i<m_list.max; i++)
	{	
		//printf("\n\nin find_f\n%s\n", funcname);
		pf = GetProcAddress(m_list.hms[i], funcname);
		//printf("test: 0x%p",GetProcAddress(m_list.hms[i],"puts"));
		if(pf)
			break;
		//printf("procaddress: %p\n",pf);
		//printf("error: %d\n",GetLastError());
	}
	return pf;
}
unsigned int alarm(unsigned int seconds)
{	
	puts("alarm was not supported");
	return 0;
}

int read(int fd, void *buf, int count)
{
	LPVOID fp = find_f("_read");
	return ((int (*)(int, void*, int))fp)(fd, buf, count);
}

int write(int fd, void *buf, int count)
{
	LPVOID fp = find_f("_write");
	return ((int (*)(int, void*, int))fp)(fd, buf, count);
}
int __isoc99_scanf(char * format, ... )
{
	LPVOID fp = find_f("scanf");	
	//另开辟新栈帧传递参数
	return ((int (*)(char *))fp)(format);
}

void init_chart()
{
//	puts("init chart");


//load module
	m_list.max = 2;
	m_list.hms[0] = LoadLibrary("msvcrt.dll");
	m_list.hms[1] = LoadLibrary("msvcrt90.dll");

//add func
	chart.max = 4;
	strcpy(chart.fitems[0].name, "alarm");
	chart.fitems[0].pf = (LPVOID*)alarm;
	strcpy(chart.fitems[1].name, "write");
	chart.fitems[1].pf = (LPVOID*)write;
	strcpy(chart.fitems[2].name, "read");
	chart.fitems[2].pf = (LPVOID*)read;
	strcpy(chart.fitems[3].name, "__isoc99_scanf");
	LPVOID fp = find_f("scanf");	
	chart.fitems[3].pf = (LPVOID*)fp;


	
//	printf("%p", chart.fitems[0].pf);
//	puts(chart.fitems[0].name);
//	puts("done init chart");
	
}
