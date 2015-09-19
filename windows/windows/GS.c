#include"stdafx.h"
#include"string.h"
#pragma strict_gs_check(on)
int vulfunction(char *str)
{
	char arry[4];
	strcpy(arry,str);
	return 1;
}
int _tmain(int argv, _TCHAR* argv[])
{
	char *str = "yeah,i have GS protection";
	vulfunction(str);
	return 0;
}
