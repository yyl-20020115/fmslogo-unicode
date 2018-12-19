.386
.model flat,stdcall 
.stack 4096 
public _do_push
.code 
_do_push proc content:dword 
		pop ebp
		pop eax
		jmp eax
_do_push endp

end 