---  
layout: post  
title: "bctf_securecom"  
date: 2015-09-29 00:19:12 +0800  
comments: true  
categories:   
---  
  
###0x00   
	 if ( a2 || !a3 )  
	  {  
	    if ( a3 != 8 || *(_QWORD *)a2 != 'ELPMISOS' )  
	    {  
	      result = 0x80004005i64;  
	    }  
###0x01  
输入SOSIMPLE  
  
  
###0x0  
CreateEvent是一个Windows API函数。它用来创建或打开一个命名的或无名的事件对象  
CoInitializeEx是 Windows提供的API函数，为当前线程初始化COM库并设置并发模式  
只有进程外Com组件才需要调用CoRegisterClassObject()  
	HRESULT CoRegisterClassObject(  
	  _In_  REFCLSID  rclsid,	//The CLSID to be registered.  
	  _In_  LPUNKNOWN pUnk,	  
	  _In_  DWORD     dwClsContext,  
	  _In_  DWORD     flags,  
	  _Out_ LPDWORD   lpdwRegister  
	);  
WaitForSingleObject 函数  
	DWORD WaitForSingleObject(  
	HANDLE hObject,  
	DWORD dwMilliseconds  
	);等待函数可使线程自愿进入等待状态，直到一个特定的内核对象变为已通知状态为止。  
BOOL CloseHandle(  
HANDLE hObject  
); 关闭一个内核对象。其中包括文件、文件映射、进程、线程、安全和同步对象等。  
CoUninitialize关闭当前线程的COM库,卸载线程加载的所有dll,释放任何其他的资源,关闭在线程上维护所有的RPC连接。  
COM是开发软件组件的一种方法。组件实际上是一些小的二进制可执行程序，它们可以给应用程序，操作系统以及其他组件提供服务  
所有的COM接口都继承了IUnknown，每个接口的vtbl中的前三个函数都是QueryInterface、AddRef、Release  
CLSID是指windows系统对于不同的应用程序，文件类型，OLE对象，特殊文件夹以及各种系统组件分配一个唯一表示它的ID代码，用于对其身份的标示和与其他对象进行区分  
QueryPerformanceCounter 來精確計算執行時間  
用指定的类标识符创建一个Com对象,用指定的类标识符创建一个未初始化的对象。当在本机中只创建一个对象时，可以调用CoCreateInstance;在远程系统中创建一个对象时，可以调用CoCreateInstanceEx;创建多个同一CLSID的对象时, 可以参考 CoGetClassObject 函数。  
otaskmemalloc 分配内存块。  
ActiveX, DirectX以及OLE等都是基于COM而建立起来的  
