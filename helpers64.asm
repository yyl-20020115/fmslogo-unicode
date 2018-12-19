.386
.model flat,stdcall 
.stack 4096 
public _do_push
.code 
_do_push proc content:qword 
		pop rbp
		pop rax
		jmp rax
_do_push endp

end 