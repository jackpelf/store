---  
layout: post  
title: "windowsexception"  
date: 2015-09-30 00:29:47 +0800  
comments: true  
categories:   
---  
###0x00 SEH基础
Windows结构化异常处理  
i386引入中端和异常，中断是外部硬件设备或异步事件产生的，异常是由内部事件产生的，分为故障、陷阱和终止。  
可以使用RaiseException引发异常  
	VOID RaiseException{  
		DWORD	dwExceptionCode,  
		DWORD	dwExceptionFlags,  
		DWORD	nNumberOfArguments  
		CONST	DWORD	*IpArguments  
		)  
按照作用域，SEH可分为两类:监视某线程是否发生异常的异常处理过程，称为线程相关的异常处理过程，称为Per_Thread异常处理，简称线程异常处理；监视整个进程中所有线程是否发生异常的异常处理过程，称为进程相关的异常处理过程，或称为final型异常处理过程。  
TEB记录线程的重要信息，ExceptionList指向异常处理结构，位于TEB偏移0处，并且fs段寄存器指向当前TEB数据。  

EXCEPTION_REGISTRATION结构用于描述多个线程异常处理嵌套层次。  
	EXCEPTION_REGISTRATION  
		prev	dd	？  
		handler	dd	?  

###0x01 SEH过程
异常处理过程  
1.如果程序处于被调试状态，则挂起程序，向调试器发送EXCEPTION_DEBUG_EVENT,dwFirstchance置1  
2.系统查找是否存在与线程相关的异常处理过程,与线程相关的异常处理过程可以有一个或多个，每个可以选择处理或不处理,如果程序线程的异常处理均选择不处理异常，再次向调试器发送EXCEPTION_DEBUG_INFO,dwFirstchance置0  
3.进程异常处理  
4.系统默认异常处理  

###0x02 异常过程
EXCEPTION_POINTERS,EXCEPTION_REOORD,CONTEXT  
当一个异常发生时，操作系统向引起异常的线程的堆栈压入EXCEPTION_POINTERS结构，EXCEPTION_POINTERS包含两个指针，一个指向EXCEPTION_RECORD结构一个指向CONTEXT  
EXCEPTION_RECORD包含最近发生异常的详细信息  
	EXCEPTION_RECORD STRUCT{  
		DWORD	ExceptionCode;异常代码  
		DWORD	ExceptionFlags;  
		struct	EXCEPTION_RECORD；指向另一个结构  
		PVOID	ExceptionAddress;发生异常的地址  
		DWORD	NumberParameters;  
		ULONG_PTR	ExceptionInformation  
	}EXCEPTION_RECORD  
  
###0x03 windows入口函数
___tmainCRTStartup入口函数   
_setargv()  
_setenvp()  
_cinit()  
    | 
    V 
_cinit()  
分为_fpmath()或_FPinit(),初始化浮点运算  
_initterm(__xi_a, __xi_z);	//c  
_initterm(__xc_a, __xc_z);	//c++  
接受两个指针，指向一张函数指针表，如果表示一个函数指针，则执行该函数，直到第二个指针结束  
    | 
    V 
_initterm(__xi_a, __xi_z);先后调用__initstdio,__initmbctable  
  
