#include <windows.h>   
HINSTANCE hInstance;   
  
class CFrameWnd     
{   
 HWND hwnd;   
public:   
 CFrameWnd();   //也可以在这里调用Create()   
 virtual ~CFrameWnd();   
 int Create();    //类就留意这一个函数就行了！   
 BOOL ShowWnd();   
};   
class CWinApp1     
{   
public:   
 CFrameWnd* m_pMainWnd;//在真正的MFC里面   
//它是CWnd指针，但这里由于不写CWnd类   
//只要把它写成CFrameWnd指针   
 CWinApp1* m_pCurrentWinApp;//指向应用程序对象本身   
 CWinApp1();   
 virtual ~CWinApp1();   
 virtual BOOL InitInstance();//MFC原本是必须重载的函数，最重要的函数！！！！   
 virtual BOOL Run();//消息循环   
};   
CFrameWnd::CFrameWnd(){}   
CFrameWnd::~CFrameWnd(){}   
  
int CFrameWnd::Create()   //封装创建窗口代码   
{   
 WNDCLASS wndcls;   
 wndcls.style=0;   
 wndcls.cbClsExtra=0;   
 wndcls.cbWndExtra=0;   
 wndcls.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);   
 wndcls.hCursor=LoadCursor(NULL,IDC_CROSS);   
 wndcls.hIcon=LoadIcon(NULL,IDC_ARROW);   
 wndcls.hInstance=hInstance;   
 wndcls.lpfnWndProc=DefWindowProc;//默认窗口过程函数。   
//大家可以想象成MFC通用的窗口过程。   
 wndcls.lpszClassName="窗口类名";   
 wndcls.lpszMenuName=NULL;   
 RegisterClass(&wndcls);   
  
 hwnd=CreateWindow("窗口类名","窗口实例标题名",WS_OVERLAPPEDWINDOW,0,0,600,400,NULL,NULL,hInstance,NULL);   
  return 0;   
}   
  
BOOL CFrameWnd::ShowWnd()//显示更新窗口   
{   
 ShowWindow(hwnd,SW_SHOWNORMAL);   
 UpdateWindow(hwnd);   
 return 0;   
}   
  
/////////////   
CWinApp1::CWinApp1()   
{   
 m_pCurrentWinApp=this;   
}   
CWinApp1::~CWinApp1(){}   
//以下为InitInstance()函数，MFC中要为CWinApp的派生类改写，   
//这里为了方便理解，把它放在CWinApp类里面完成！   
//你只要记住真正的MFC在派生类改写此函数就行了。   
BOOL CWinApp1::InitInstance()   
{   
 m_pMainWnd=new CFrameWnd;   
 m_pMainWnd->Create();   
 m_pMainWnd->ShowWnd();   
 return 0;   
}   
  
BOOL CWinApp1::Run()//////////////////////封装消息循环   
{   
 MSG msg;   
 while(GetMessage(&msg,NULL,0,0))   
 {   
  TranslateMessage(&msg);   
  DispatchMessage(&msg);   
 }   
 return 0;   
} //////////////////////////////////////////////////////封装消息循环   
  
CWinApp1 theApp;   //应用程序对象（全局）   
  
int WINAPI WinMain( HINSTANCE hinst, HINSTANCE hPrevInstance,   LPSTR lpCmdLine,  int nCmdShow)   
{   
 hInstance=hinst;   
 CWinApp1* pApp=theApp.m_pCurrentWinApp;   
//真正的MFC要写一个全局函数AfxGetApp，以获取CWinApp指针。   
 pApp->InitInstance();   
 pApp->Run();   
 return 0;   
}  
