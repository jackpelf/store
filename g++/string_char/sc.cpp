#include<iostream>
#include<string.h>
using namespace std;
int main()
{
	char buf[10] = "AAAAAAAAA";
	buf[0] = 0;
	string s = buf;
	cout<<s.length()<<endl;
	cout<<strlen(s.c_str())<<endl;
	return 0;
}
