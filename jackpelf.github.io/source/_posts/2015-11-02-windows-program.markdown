---
layout: post
title: "windows-program"
date: 2015-11-02 19:17:53 +0800
comments: true
categories: 
---



###mfc
CDialog类是在屏幕上显示的对话框基类   
类CCmdTarget是MFC类库中消息映射体系的一个基类，是MFC处理命令消息的基础、核心。消息映射把命令或消息引导给用户为之编写的响应函数  
CEdit提供了Windows编辑控件的功能  
CWnd是MFC窗口类的基类  
LRESULT SendMessage（HWND hWnd，UINT Msg，WPARAM wParam，LPARAM IParam）
该函数将指定的消息发送到一个或多个窗口    
Windows对话框分为两类：模态对话框和非模态对话框。  
模态对话框弹出后本应用程序其他窗口不再接受用户输入，只有相应操作退出后，其他窗口才能继续与用户交互  
非模态对话框在它弹出后其他窗口仍能响应用户输入  
当dlg.DoModal()后，显示一个模态对话框，此时DoModal()函数并不返回，直到用户关闭此对话框时，DoModal才返回  
CWinApp*AFXAPI AfxGetApp();返回指向应用程序的单一的CWinApp对象的指针  
OnSysCommand（）这个函数主要是截获控制命令的,尤其是最大化和最小化窗口的时候  
CWinApp::Run提供了一个默认的消息循环。Run函数获得和分派一个windows消息直到应用程序接收一个WM_QUIT消息  
MessageBox是API，因此它需要HWND参数指定其所属窗体  
CWnd::MessageBox() 是CWnd的成员函数，它要求MessageBox只能在cwnd类及其子类中使用  
AfxMessageBox（）mfc中的全局函数，无句柄HWND参数  
MFC基类关系  

	CObject
	|
	-CCmdTarget
	  |
	  -CWnd
	   |
	   -CDialog




