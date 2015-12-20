---
layout: post
title: "c++class"
date: 2015-12-19 18:47:53 +0800
comments: true
categories: 
---
```c
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
```
