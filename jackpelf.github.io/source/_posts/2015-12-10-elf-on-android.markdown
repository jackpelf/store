---
layout: post
title: "elf-on-android"
date: 2015-12-10 22:49:16 +0800
comments: true
categories: 
---
#android


###可执行方法
添加/lib目录
中间添加ld-linux.so.3
/system/lib/中添加各种lib

###gdbserver
gdbserver 地址端口号 ./程序  
可以使用ida进行调试  
也可以在linux中使用
arm-linux-gdb ./test-debug
target remote 192.168.183.127:2345

```c
#include<stdio.h>
int main()
{
	char buf[20];
	puts("pwn me");
	scanf("%s",buf);
	printf("%s",buf);
	return 0;
}
```

###使用nc挂程序
nc -l -p 8888 -e ./pwnme

nc循环脚本
``` bash
echo server running
while :
do
nc -l -p 8888 -e ./$1
echo done
done
```

###arm details
arm 寄存器
r0~r7未分组寄存器
r8~r14分组寄存器
sp(r13)
lr(r14)链接寄存器保存子程序返回地址
pc(r15)
cpsr(r16)程序状态寄存器
r11桢指针

   r0,r1,r2,r3,在调用函数时，用来存放前4个函数参数和返回值
