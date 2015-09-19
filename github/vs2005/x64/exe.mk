OUT = test.exe
EXE = test
OBJ = *.obj
C = *.cpp
RES =

LINK_FLAG =  /out:$(OUT) /libpath:D:\Blue\Compiling\Vs2005\VC\lib\amd64 /libpath:D:\Blue\Compiling\Vs2005\VC\PlatformSDK\Lib\AMD64
CL_FLAG = /c /I D:\Blue\Compiling\Vs2005\VC\PlatformSDK\Include /I D:\Blue\Compiling\Vs2005\VC\include


#link
$(EXE) : $(OBJ)
	D:\Blue\Compiling\Vs2005\VC\bin\amd64\Link.exe $(LINK_FLAG) $(OBJ)

#compile
$(OBJ) : $(C)
	D:\Blue\Compiling\Vs2005\VC\bin\amd64\cl.exe $(CL_FLAG) $(C)

clean:  
      del*.obj  
      del*.res 

