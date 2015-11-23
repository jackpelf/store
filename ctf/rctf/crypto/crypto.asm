.386
.model flat, stdcall
option casemap :none
include mh.h
bufferSize equ 128
.data
	hStdin    DWORD ?
	hStdout   DWORD ?
	dwNum 	  DWORD ?
	cLen      DWORD ?
	buffer    db bufferSize+2 dup(0)
	buffer2	  db bufferSize*3 dup(0)
	buffer3   db bufferSize*3 dup(0) 
	ca 		  db '0123456789abcdef'  
	tt      DWORD ?
.code
GetStdIO:
	invoke     GetStdHandle,STD_INPUT_HANDLE
    mov     hStdin,eax
	invoke     GetStdHandle,STD_OUTPUT_HANDLE
    mov     hStdout,eax
	ret
	
func1 proc var1
	push ebx
	push ecx
		mov eax,var1
		mov ah,al
		and al,00001111b
		and ah,11110000b
		shr ah,4		
		lea ebx,ca
		movzx ecx,al
		mov al,[ebx+ecx]
		movzx ecx,ah
		mov ah,[ebx+ecx]
	pop ecx
	pop ebx
	ret
endp	

c2w proc s1,s2,l
	local  @temp
	pushad
	xor ecx,ecx
	mov ebx,s1
	xor edx,edx
	.while dword ptr ecx<l
		mov dl,[ebx+ecx]
		invoke func1,edx
		mov edx,s2
		mov byte ptr [ecx*2+edx],ah
		mov byte ptr [ecx*2+edx+1],al
		inc ecx
	.endw
	popad
	ret
endp

mInit proc s,l
local @temp
	pushad
		mov ebx,s
		mov ecx,l
		mov eax,0
		xor edx,edx
		mov @temp,1
		.while ecx<bufferSize
			mov dl,[eax+ebx]
			add	edx,@temp
			mov [ecx+ebx],dl
			inc ecx
			inc eax
			.if eax==l
				xor eax,eax
				add @temp,1
			.endif
		.endw
		
		mov ecx,0
		mov eax,l
		.while ecx<bufferSize
			mov dl,[ebx+ecx]
			xor dl,al
			mov [ebx+ecx],dl
			inc ecx
		.endw
	popad
	ret
endp

Encode proc s,l
	local @k
	pushad
		mov ebx,s
		mov ecx,0
		mov @k,8
		.while ecx<l
			xor edx,edx
			mov eax,ecx
			div @k
			.if edx!=0
				mov dl,[ebx+ecx-1]
			.endif
			.if eax!=0
				mov al,[ebx+ecx-8]
			.endif 
			mov ah,[ebx+ecx]
			xor ah,al
			xor ah,dl
			mov [ebx+ecx],ah
			inc ecx
		.endw
	popad
	ret
endp
	
dfs proc s,t
	pushad 
		mov ecx,t
		.if ecx>=bufferSize*2
			jmp dfs_jmp
		.endif
		mov ebx,s
		mov eax,t
		add eax,eax
		inc eax
		invoke dfs,s,eax
		mov dl,[ebx+ecx]
		mov ecx,tt
		lea ebx,buffer3
		mov [ebx+ecx],dl
		inc ecx
		mov tt,ecx
		inc eax
		invoke dfs,s,eax
dfs_jmp:		
	popad
	ret
endp

start:
	pushad
	call GetStdIO
	jmp1:
		invoke  ReadConsole,hStdin,offset buffer,bufferSize+2,offset cLen,NULL
		sub cLen,1			
		mov byte ptr [buffer3+bufferSize*2],10
		mov byte ptr [buffer2+bufferSize*2],10
		invoke mInit,addr buffer,cLen
		invoke Encode,addr buffer,bufferSize
		invoke c2w,addr buffer,addr buffer2,bufferSize
		mov tt,0
		invoke dfs,addr buffer2,0
		invoke WriteConsole,hStdout,offset buffer3,bufferSize*2+1,offset dwNum,NULL
	jmp jmp1
	popad
	ret
end start 
