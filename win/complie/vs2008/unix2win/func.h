/*
only for func search and hook
*/
#include<string.h>
//#define DEBUG

fchart chart;		//self defined func
hmlist m_list;		//dll list

LPVOID find_func_indll(char* funcname)
{
	int i;
	LPVOID pf=NULL;
	for(i=0; i<=m_list.max; i++)
	{	
		char name[40];
		pf = GetProcAddress(m_list.hms[i], funcname);		//direct
		if(pf)
			break;

		pf = GetProcAddress(m_list.hms[i], funcname + 1);	//cut one _
		if(pf)
			break;
		
		pf = GetProcAddress(m_list.hms[i], funcname + 2);	//cut two _
		if(pf)
			break;
		
		pf = GetProcAddress(m_list.hms[i], funcname + 3);	//_IO
		if(pf)
			break;

		pf = GetProcAddress(m_list.hms[i], funcname + 4);	//_IO_
		if(pf)
			break;
	
		pf = GetProcAddress(m_list.hms[i], funcname + 9);	//__isoc99_
		if(pf)
			break;
		
		name[0] = '_';
		name[1] = '_';
		strcpy(name + 2, funcname);
	
		pf = GetProcAddress(m_list.hms[i], name + 1);		//add one _
		if(pf)
			break;
		
		pf = GetProcAddress(m_list.hms[i], name + 0);		//add two _
		if(pf)
			break;
	}
	return pf;
}



unsigned int alarm(unsigned int seconds)
{	
	puts("alarm was not supported");
	return 0;
}

int _IO_getc(FILE *fp)
{	
	return (int)getchar();
}



void init_chart()
{
#ifdef DEBUG
	puts("init chart");
#endif

//load module
	m_list.max = 0;
	m_list.hms[m_list.max] = LoadLibrary("msvcrt.dll");
	if(GetLastError() == 0)	m_list.max ++;
	m_list.hms[m_list.max] = LoadLibrary("msvcrt90.dll");
	if(GetLastError() == 0)	m_list.max ++;

//add func
	chart.max = -1;
	strcpy(chart.fitems[++chart.max].name, "alarm");
	chart.fitems[chart.max].pf = (LPVOID*)alarm;
	strcpy(chart.fitems[++chart.max].name, "_IO_getc");
	chart.fitems[chart.max].pf = (LPVOID*)_IO_getc;
	


	
#ifdef DEBUG
	printf("m_list.max : %d\n", m_list.max);
	puts("done init chart");
#endif	
}
