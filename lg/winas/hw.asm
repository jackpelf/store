.386
.model flat, stdcall
option casemap: none

include windows.inc
include kernel32.inc
include user32.inc

includelib kernel32.lib
includelib user32.lib

.data
szCaption   db  "Hello", 0
szText      db  "Hello World!", 0

.code

func PROC
    INVOKE MessageBox, NULL, addr szText, addr szCaption, MB_OK
func ENDP

main PROC
	INVOKE func
	INVOKE ExitProcess, 0
main ENDP
END main
