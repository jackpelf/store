#include<iostream>
using namespace std;

class base
{
public:	
	base()
	{
		cout<<"base cont"<<endl;
	}
private:
	char buf[20];
};
class devi:base
{
public:
	devi()
	{
		cout<<"devi cont"<<endl;
	}
};
int main()
{
	devi test;
	return 0;
}
