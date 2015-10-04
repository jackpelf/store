---  
layout: post  
title: "windows_异常"  
date: 2015-10-04 19:53:12 +0800  
comments: true  
categories:   
---  
  
###0x00 windows异常处理  
VC将SEH封装成__try __catch __finally __leave  
c++中为try catch throw  
每一个SEH异常都有一个与其相关联的异常码（exception code）。你可以使用GetExceptionCode()函数来获取异常码。你可以通过GetExceptionInformation()来获取异常信息。为了使用这些函数，需要定制自己的exception filter  
  
VEH  
当程序中的某些部分发生SEH异常时，系统依次调用已安装的VEH处理器，直到它找到有用的SEH处理器  
  
CRT  
当CRT遇到一个未被处理的C++类型化异常时，它会调用terminate()函数。如果你想拦截这个调用并提供合适的行为，你应该使用set_terminate()函数设置错误处理器(error hanlder)。  
  
c++信号处理  
C++提供了被称为信号的中断机制。你可以使用signal()函数处理信号。  
Visual C++提供了6中类型的信号：  
l SIGABRT Abnormal termination  
l SIGFPE Floating-point error  
l SIGILL Illegal instruction  
l SIGINT CTRL+C signal  
l SIGSEGV Illegal storage access  
l SIGTERM  
  
###0x01 异常处理栈结构  
EXCEPTION_REGISTRATION结构  
  
	struct EXCEPTION_REGISTRATION{  
		prev	dd	?  
		handler	dd	?  
	}  
prev指向前一个EXCEPTION_REGISTRATION  
handler指向异常处理代码  
		 _______________  
	fs[0]-->|  指向下一个   |----  
		|_______________|   |  
		| 处理程序1地址	|   |  
		|_______________|   |  
				    |  
		 _______________    |  
                |  指向下一个   |<--|  
                |_______________|____  
                | 处理程序2地址	|   |  
                |_______________|   |  
				    |  
		 _______________    |  
       结束地址 |  FFFFFFFFh    |<--|  
                |_______________|  
                | 处理程序3地址	|  
                |_______________|  
  
###0x02 SEH处理过程  
1.安装SEH  
当线程初始化时，会在栈中安装一个SEH作为线程默认异常处理  
在使用__try{}__except()会在当前函数帧中安装一个SEH  
2.SEH状态  
多个SEH存在栈上,通过链表指针由栈顶向栈底串成单向链表  
最顶端的SEH通过TEB0偏移处标识  
3.SEH处理过程  
异常发生时，操作系统会中断程序，从TEB的0偏移处取出距离栈顶最近的SEH，使用异常处理函数处理异常  
当最近的异常处理函数失败时，顺着SEH链表依次尝试其他异常处理函数  
如果程序安装的所有异常处理函数不能处理，系统将使用系统默认的异常处理函数  
  
  
  
  
  
###0x03 实际SEH数据结构  
EXCEPTION_REGISTRATION  
  
	struct	EXCEPTION_REGISTRATION{  
		struct _EXCEPTION_REGISTRATION *prev;  
		void (*handler)(    PEXCEPTION_RECORD,  
				    PEXCEPTION_REGISTRATION,  
				    PCONTEXT,  
				    PEXCEPTION_RECORD);  
		struct scopetable_entry *scopetable;  
		int 	trylevel;  
		int 	ebp;  
	}  
  
其中SCOPETABLE 定义如下  
  
	struct _EH4_SCOPETABLE {  
		 UINT GSCookieOffset;  
		 UINT GSCookieXOROffset;  
		 UINT EHCookieOffset;  
		 UINT EHCookieXOROffset;  
		 _EH4_SCOPETABLE_RECORD ScopeRecord[1];  
	};  
  
其中ScopeRecord定义如下  
  
	struct _EH4_SCOPETABLE_RECORD {      
	     DWORD EnclosingLevel;       //上一层__try块      
	     PVOID FilterFunc;           //过滤表达式      
	     union      
	     {      
		 PVOID HandlerAddress;   //__except块代码      
		 PVOID FinallyFunc;      //__finally块代码      
	     };      
	};    
  
  
  
  
###0x04  pe程序开始桩代码  
_onexit_nolock(func)	注册退出时执行的函数  
start函数跳到_tmainCRTStartup函数  
  
###0x05 ollydbg  
ollydbg   
restart 	ctrl+f2  
run		f9  
  
###0x06 except处理  
_except() 括号里的是 Exception Filter 表达式，表达式的计算结果有 3 个值：  
EXCEPTION_EXECUTE_HANDLER = 1	被识别  
EXCEPTION_CONTINUE_SEARCH = 0	继续到上一层查找恰当的_except模块  
EXCEPTION_CONTINUE_EXECUTION = -1	被忽略  
  
  
  
  
  
  
  
