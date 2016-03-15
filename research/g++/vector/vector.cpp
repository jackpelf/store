#include<iostream>
#include<vector>
using namespace std;

int main()
{
	vector<int> vec;
	while(1)
	{
		int tmp;
		cin>>tmp;
		if(tmp == 0)
			break;
		vec.push_back(tmp);
	}
	cout<<vec[vec.size()-1]<<endl;
	cout<<"address :"<<&vec[0]<<endl;
	cout<<"size: "<<vec.size()<<endl;
	cout<<"capacity : "<<vec.capacity()<<endl;
	return 0;
}
