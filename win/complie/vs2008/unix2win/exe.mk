OUT = out\out.exe 
EXE = test
OBJ = *.obj
C = *.cpp
RES =

LINK_FLAG =  /out:$(OUT) /libpath:F:\compile\VC2008\lib /libpath:F:\compile\VC2008\PlatformSDK\Lib
CL_FLAG = /c /I F:\compile\vc2008\PlatformSDK\Include /I F:\compile\VC2008\include 


#link
$(EXE) : $(OBJ)
	Link $(LINK_FLAG) $(OBJ)

#compile
$(OBJ) : $(C)
	CL $(CL_FLAG) $(C)

clean:  
      del *.obj  
      del *.res 

