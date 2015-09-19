OUT = test.exe
EXE = test
OBJ = *.obj
C = *.c
RES =

LINK_FLAG =  /out:$(OUT) /libpath:D:\Blue\Compiling\VC2008\lib /libpath:D:\Blue\Compiling\VC2008\PlatformSDK\Lib
CL_FLAG = /c /I D:\blue\Compiling\VC2008\h


#link
$(EXE) : $(OBJ)
	Link $(LINK_FLAG) $(OBJ)

#compile
$(OBJ) : $(C)
	CL $(CL_FLAG) $(C)

clean:  
      del*.obj  
      del*.res 

