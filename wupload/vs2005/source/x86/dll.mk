OUT = test.dll
DLL = debug
OBJ = *.obj
C = *.cpp
RES =

LINK_FLAG = /out:$(OUT) /dll $(OBJ) /libpath:D:\Blue\Compiling\Vs2005\VC\lib /libpath:D:\Blue\Compiling\Vs2005\VC\PlatformSDK\lib
CL_FLAG = /c /I D:\Blue\Compiling\Vs2005\VC\PlatformSDK\Include /I D:\Blue\Compiling\Vs2005\VC\include


#link
$(DLL) : $(OBJ)
	D:\Blue\Compiling\Vs2005\VC\bin\Link.exe $(LINK_FLAG)

#compile
$(OBJ) : $(C)
	D:\Blue\Compiling\Vs2005\VC\bin\cl.exe $(CL_FLAG) $(C)


