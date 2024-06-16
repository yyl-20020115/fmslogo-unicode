public _do_push
.code 
_do_push proc content:qword 
		pop rbp
		pop rax
		jmp rax
		ret
_do_push endp

end 