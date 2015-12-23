#include <windows.h>   
HINSTANCE hInstance;   
  
class CFrameWnd     
{   
 HWND hwnd;   
public:   
 CFrameWnd();   //Ҳ�������������Create()   
 virtual ~CFrameWnd();   
 int Create();    //���������һ�����������ˣ�   
 BOOL ShowWnd();   
};   
class CWinApp1     
{   
public:   
 CFrameWnd* m_pMainWnd;//��������MFC����   
//����CWndָ�룬���������ڲ�дCWnd��   
//ֻҪ����д��CFrameWndָ��   
 CWinApp1* m_pCurrentWinApp;//ָ��Ӧ�ó��������   
 CWinApp1();   
 virtual ~CWinApp1();   
 virtual BOOL InitInstance();//MFCԭ���Ǳ������صĺ���������Ҫ�ĺ�����������   
 virtual BOOL Run();//��Ϣѭ��   
};   
CFrameWnd::CFrameWnd(){}   
CFrameWnd::~CFrameWnd(){}   
  
int CFrameWnd::Create()   //��װ�������ڴ���   
{   
 WNDCLASS wndcls;   
 wndcls.style=0;   
 wndcls.cbClsExtra=0;   
 wndcls.cbWndExtra=0;   
 wndcls.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);   
 wndcls.hCursor=LoadCursor(NULL,IDC_CROSS);   
 wndcls.hIcon=LoadIcon(NULL,IDC_ARROW);   
 wndcls.hInstance=hInstance;   
 wndcls.lpfnWndProc=DefWindowProc;//Ĭ�ϴ��ڹ��̺�����   
//��ҿ��������MFCͨ�õĴ��ڹ��̡�   
 wndcls.lpszClassName="��������";   
 wndcls.lpszMenuName=NULL;   
 RegisterClass(&wndcls);   
  
 hwnd=CreateWindow("��������","����ʵ��������",WS_OVERLAPPEDWINDOW,0,0,600,400,NULL,NULL,hInstance,NULL);   
  return 0;   
}   
  
BOOL CFrameWnd::ShowWnd()//��ʾ���´���   
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
//����ΪInitInstance()������MFC��ҪΪCWinApp���������д��   
//����Ϊ�˷�����⣬��������CWinApp��������ɣ�   
//��ֻҪ��ס������MFC���������д�˺��������ˡ�   
BOOL CWinApp1::InitInstance()   
{   
 m_pMainWnd=new CFrameWnd;   
 m_pMainWnd->Create();   
 m_pMainWnd->ShowWnd();   
 return 0;   
}   
  
BOOL CWinApp1::Run()//////////////////////��װ��Ϣѭ��   
{   
 MSG msg;   
 while(GetMessage(&msg,NULL,0,0))   
 {   
  TranslateMessage(&msg);   
  DispatchMessage(&msg);   
 }   
 return 0;   
} //////////////////////////////////////////////////////��װ��Ϣѭ��   
  
CWinApp1 theApp;   //Ӧ�ó������ȫ�֣�   
  
int WINAPI WinMain( HINSTANCE hinst, HINSTANCE hPrevInstance,   LPSTR lpCmdLine,  int nCmdShow)   
{   
 hInstance=hinst;   
 CWinApp1* pApp=theApp.m_pCurrentWinApp;   
//������MFCҪдһ��ȫ�ֺ���AfxGetApp���Ի�ȡCWinAppָ�롣   
 pApp->InitInstance();   
 pApp->Run();   
 return 0;   
}  
