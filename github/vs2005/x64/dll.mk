OUT = test.dll
DLL = debug
OBJ = *.obj
C = *.cpp
RES =

LINK_FLAG = /out:$(OUT) /dll $(OBJ) /libpath:D:\Blue\Compiling\Vs2005\VC\lib\amd64 /libpath:D:\Blue\Compiling\Vs2005\VC\PlatformSDK\Lib\AMD64
CL_FLAG = /c /I D:\Blue\Compiling\Vs2005\VC\PlatformSDK\Include /I D:\Blue\Compiling\Vs2005\VC\include


#link
$(DLL) : $(OBJ)
	D:\Blue\Compiling\Vs2005\VC\bin\amd64\Link.exe $(LINK_FLAG)

#compile
$(OBJ) : $(C)
	D:\Blue\Compiling\Vs2005\VC\bin\amd64\cl.exe $(CL_FLAG) $(C)


