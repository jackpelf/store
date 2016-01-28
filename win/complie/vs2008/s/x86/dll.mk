OUT = test.dll
DLL = debug
OBJ = *.obj
C = *.cpp
RES =

LINK_FLAG = /out:$(OUT) /dll $(OBJ) /libpath:F:\compile\VC2008\lib /libpath:F:\compile\VC2008\PlatformSDK\Lib
CL_FLAG = /c /I F:\compile\vc2008\PlatformSDK\Include /I F:\compile\VC2008\include 


#link
$(DLL) : $(OBJ)
	Link $(LINK_FLAG)

#compile
$(OBJ) : $(C)
	CL $(CL_FLAG) $(C)


