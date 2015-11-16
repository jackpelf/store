OUT = test.dll
DLL = debug
OBJ = *.obj
C = *.cpp
RES =

LINK_FLAG = /out:$(OUT) /dll $(OBJ) /libpath:D:\Blue\Compiling\VC2008\lib /libpath:D:\Blue\Compiling\VC2008\PlatformSDK\Lib
CL_FLAG = /c /I d:\Blue\Compiling\vc2008\PlatformSDK\Include /I D:\Blue\Compiling\VC2008\include 


#link
$(DLL) : $(OBJ)
	Link $(LINK_FLAG)

#compile
$(OBJ) : $(C)
	CL $(CL_FLAG) $(C)


