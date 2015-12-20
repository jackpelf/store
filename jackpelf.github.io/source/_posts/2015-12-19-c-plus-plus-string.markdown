---
layout: post
title: "c++string"
date: 2015-12-19 18:52:39 +0800
comments: true
categories: 
---
```c
#include<stdio.h>
#include<string.h>
using namespace std;
int func0()
{
	char buf[20];
	string s = "test";
	puts("string from char");
	return 0;
}

int func1()
{
	string s = "test";
	puts("string from conststr");
	return 0;
}

int func2()
{
	string s0;
	string s1;
	puts("two string");
	return 0;
}
int func3()
{
	string s0 = "test";
	string s1 = s0;
	puts("string from string");
	return 0;
}
int func4()
{
	string *p = new string("test");
	puts("string from new");
	return 0;
}
int main()
{
	func0();
	func1();
	func2();
	func3();
	func4();
	return 0;
}
```
