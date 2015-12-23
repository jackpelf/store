OUT = test.exe
EXE = test
OBJ = *.obj
C = *.cpp
RES =

LINK_FLAG =  /out:$(OUT) /libpath:D:\Blue\Compiling\VC2008\lib /libpath:D:\Blue\Compiling\VC2008\PlatformSDK\Lib /libpath:D:\blue\Compiling\VC2008\atlmfc\lib
CL_FLAG = /c /I d:\Blue\Compiling\vc2008\PlatformSDK\Include /I D:\Blue\Compiling\VC2008\include /I D:\blue\Compiling\VC2008\atlmfc\include


#link
$(EXE) : $(OBJ)
	Link $(LINK_FLAG) $(OBJ)

#compile
$(OBJ) : $(C)
	CL $(CL_FLAG) $(C)

clean:  
      del*.obj  
      del*.res 

