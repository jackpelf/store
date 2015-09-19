---
layout: post
title: "bz2 decompress in C"
date: 2015-09-09 00:57:25 +0800
comments: true
categories: 
---
###0x00 source

	#include<stdio.h>
	#include<bzlib.h>
	void func1()
	{
		int i;
		int *pi = &i;
		BZFILE *b;
		char buf[20000] = "error";
		int len;
		b = BZ2_bzopen("ttt.bz2", "r");
		BZ2_bzRead(pi, b, buf, 1000);
		puts(buf);
	}

	int main()
	{
		func1();
		return 0;
	}

###0x01 compile

	gcc a.c -lbz2
