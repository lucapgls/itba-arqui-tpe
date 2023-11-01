GLOBAL cpuVendor
GLOBAL rtcTime
GLOBAL asm_get_key
GLOBAL scanf

GLOBAL test_write

GLOBAL asm_sound, asm_nosound

section .text
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

rtcTime:
	push rbp
	mov rbp, rsp

	mov rax, rdi
	out 0x70, al
	in al, 0x71

	leave
	ret

; get the key pressed (or wait until its pressed)
asm_get_key:

	xor rax, rax

	.loop:
	in al, 0x64
	and al, 0x01
	cmp al, 0
	je .loop

	in al, 0x60

	ret



test_write:

    mov rax, 1
    int 0x80
    ret

asm_sound:
	push rbp
	mov rbp,rsp

	mov al,182 	;configuro altavoz
	out 43h,al

	mov ax,di	;frecuencia en bx
	out 42h,al	;envio byte - significativo
	mov al,ah
	out 42h,al	;envio byte + significativo

	in al,61h
	or al,3h
	out 61h,al

	leave
	ret

asm_nosound:
	push rbp
	mov rbp,rsp

	in al,61h
	and al,0fch
	out 61h,al

	leave
	ret


