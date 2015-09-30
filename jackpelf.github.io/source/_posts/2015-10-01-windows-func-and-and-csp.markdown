---  
layout: post  
title: "windows_func&amp;&amp;CSP"  
date: 2015-10-01 00:52:01 +0800  
comments: true  
categories:   
---  
###0x00  
GetExceptionCode()函数来获取异常码  
向量化异常处理(VEH)是结构化异常处理的一个扩展  
AddVectoredExceptionHandler()函数添加一个向量化异常处理器  
单步中断(INT1)是由机器内部状态引起的一种中断,当系统标志寄存器的TF标志(单步跟踪标志)被置位时,就会自动产生一次单步中断,使得CPU能在执行一条指令后停下来,并显示各寄存器的内容  
  
###0x01  
jetTickCount是函数。GetTickCount返回（retrieve）从操作系统启动所经过（elapsed）的毫秒数  
	BOOL ReadFile(  
	    HANDLE hFile,                                    //文件的句柄  
	    LPVOID lpBuffer,                                //用于保存读入数据的一个缓冲区  
	    DWORD nNumberOfBytesToRead,    //要读入的字节数  
	    LPDWORD lpNumberOfBytesRead,    //指向实际读取字节数的指针  
	    LPOVERLAPPED lpOverlapped  
	    //如文件打开时指定了FILE_FLAG_OVERLAPPED，那么必须，用这个参数引用一个特殊的结构。  
	    //该结构定义了一次异步读取操作。否则，应将这个参数设为NULL  
	)  
  
	typedef struct CPPEH_RECORD        
	{        
	    DWORD old_esp;  //ESP       
	    DWORD exc_ptr;  //GetExceptionInformation返回值       
	    DWORD prev_er;  //prev _EXCEPTION_REGISTRATION_RECORD       
	    DWORD handler;  //handler       
	    DWORD msEH_ptr; //scopetable       
	    DWORD disabled; //trylevel       
	}CPPEH_RECORD,*PCPPEH_RECORD;  ;  
__local_unwind2函数是结构化异常处理的局部展开函数.  
memmove用于从src拷贝count个字符到dest  
  
  
### CSP  
BOOL WINAPI CryptAcquireContext(  
  _Out_ HCRYPTPROV *phProv,  
  _In_  LPCTSTR    pszContainer,  
  _In_  LPCTSTR    pszProvider,  
  _In_  DWORD      dwProvType,  
  _In_  DWORD      dwFlags  
);  
CryptAcquireContext,获得指定CSP 的密钥容器的句柄  
  
BOOL WINAPI CryptStringToBinary(  
  _In_    LPCTSTR pszString,  
  _In_    DWORD   cchString,  
  _In_    DWORD   dwFlags,  
  _In_    BYTE    *pbBinary,  
  _Inout_ DWORD   *pcbBinary,  
  _Out_   DWORD   *pdwSkip,  
  _Out_   DWORD   *pdwFlags  
);  
CryptStringToBinary,把格式化的字符串转换成二进制序列  
  
BOOL WINAPI CryptDecodeObjectEx(  
  _In_          DWORD              dwCertEncodingType,  
  _In_          LPCSTR             lpszStructType,  
  _In_    const BYTE               *pbEncoded,  
  _In_          DWORD              cbEncoded,  
  _In_          DWORD              dwFlags,  
  _In_          PCRYPT_DECODE_PARA pDecodePara,  
  _Out_         void               *pvStructInfo,  
  _Inout_       DWORD              *pcbStructInfo  
);  
CryptDecodeObjectEx,对lpszStructType 结构进行解码，此函数支持内存分配选项  
CryptImportPublicKeyInfo,把公钥信息导入CSP 并且返回它的句柄  
  
BOOL WINAPI CryptDecrypt(  
  _In_    HCRYPTKEY  hKey,	//A handle to the key to use for the decryption  
  _In_    HCRYPTHASH hHash,	//A handle to a hash object.  
  _In_    BOOL       Final,	//若只有一个分组的数据需要加密或者为最后一个分组，则Final为TRUE  
  _In_    DWORD      dwFlags,  
  _Inout_ BYTE       *pbData,	//The buffer holding the data to be decrypted  
  _Inout_ DWORD      *pdwDataLen	//加密的分组长度的地址  
);  
CryptDecrypt,使用指定加密密钥来解密一段密文  
  
  
  
