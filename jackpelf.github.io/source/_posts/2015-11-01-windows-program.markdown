---
layout: post
title: "windows-program"
date: 2015-11-01 21:10:52 +0800
comments: true
categories: 
---


###windowsgui程序
windows程序进行依靠外部发生的事件来驱动。
程序不断等待可能的输入，然后判断，做适当处理  
输入是由操作系统捕捉，以消息形式进入程序之中  
USER模块掌管各个外围的驱动程序    
程序调用GetMessage取得消息，程序的生命靠它来推动  

    typedef struct tagMSG
    {
        HWND    hwnd;
        UINIT       message;
        WPARAM  wParam;
        LPARAM  lParam;
        DWORD   time;
        POINT   pt;
        }MSG;

接受并处理消息的主角就是窗口  
每个窗口都应该有一个函数负责处理消息  
windows使用RegisterClass注册窗口，CreateWindow产生窗口，ShowWindow显示窗口  
TranslateMessage转化消息，DispatchMessage传递消息给窗口  
窗口函数的形式

    LRESULT CALLBACK WndProc(HWND hwnd,
                                                                UINT    message,
                                                                WPARA wParam,
                                                                LPAARAM lParam)
                                                                

对话框依其父窗口关系分为modal对话框，modeless对话框  
做出一个对话框必须有对话框模版和对话框函数  
对话框函数类似窗口函数，但是它通常只处理WM_INITDIALOG和WM_COMMAND两个消息 
对话框的激活与结束靠的是DialogBox和EndDialog  
资源描述文件(.RC)是一个以文字描述资源的地方
常用的资源有ICON/CURSOR/BITMAP/PONT/DIALOG/MENU..  
空闲时间是系统中没有任何消息等待处理
如果程序使用定制器，会送来WM_TIMER  
鼠标移动，WM_MOUSEMOVE    
console程序编译指定/D_CONSOLE,链接时指定subsystem为console  

###核心对象  

    event   CreateEvent
    mutex   CreateMutex
    semaphore   CreateSemaphore
    file    CreateFile
    file-mapping    CreateFileMapping
    process CreateProcess
    thread  CreateThread
    
前三者用于线程同步化，file-mapping用于内存映射文件  
这些API都会获得一个handle，每使用依次，对应的计数器加1  
核心对象都使用CloseHandle结束  

###MFC
WIN32API程序中程序的入口为WinMain函数
在WinMain函数中完成注册窗口创建窗口，进入消息循环，根据操作系统发送的消息调用程序的窗口函数。  
在MFC程序中是一个派生自CWinApp的全局对象  
CWinApp类被称为应用程序对象。  
CWinApp类的构造函数可以对HWND、HINSTANCE初始化  
调用完CWinApp的构造函数，将调用AfxWinMain  
AfxWinMain函数中调用AfxGetApp函数获得应用程序对象，这时将调用AfxInit全局函数  
AfxInit全局函数是使用AfxWinMain函数的参数初始化相关句柄数据成员  
之后调用CwinApp::InitApplication函数，用来初始化应用程序对象中关于文档部分的内容  
随后调用CWinApp::InitInstance函数，这个成员函数使用new在堆上声明一个框架窗口，导致框架窗口对象的构造函数被调用
在框架窗口构造函数中调用Create来创建窗口，之后调用ShowWindow、UpdateWindow向窗口发送WM_PAINT消息  
AfxWinMain调用CWinApp::Run成员函数，由这个函数创建和处理消息循环  
用户按下关闭按钮后，操作系统发送WM_CLOSE消息，程序调用DestoryWindow并发送WM_DESTORY消息，应用程序接受到这个消息后调用PostQuitMessage函数，这个函数发送WM_QUIT消息。应用程序接收到WM_QUIT消息后循环结束
AfxWinMain函数调用AfxTerm函数清理程序使用的资源并结束整个程序


