GLOBAL cpuVendor
GLOBAL rtcTime
GLOBAL asm_get_key
GLOBAL scanf

GLOBAL test_write

GLOBAL asm_start_sound, asm_end_sound

global outb, inb

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

asm_start_sound:
	push rbp
	mov rbp,rsp

	mov al,182 	;configuro altavoz
	out 0x43,al

	mov ax,di	;frecuencia en bx
	out 0x42,al	;envio byte - significativo
	mov al,ah
	out 0x42,al	;envio byte + significativo

	in al,0x61
	or al,0x03
	out 0x61,al

	leave
	ret

asm_end_sound:
	push rbp
	mov rbp,rsp

	in al,0x6
	and al,0xFC
	out 0x61,al

	leave
	ret


inb:				; Funciones para el correcto funcionamiento del soundDriver
	push rbp
	mov rbp, rsp

    mov rdx,rdi
    in al,dx		; pasaje en 8 bits

	mov rsp, rbp
	pop rbp
	ret

outb:
	push rbp
	mov rbp, rsp

    mov rax, rsi    
    mov rdx, rdi
	out dx, al		; pasaje en 8 bits

	mov rsp, rbp
	pop rbp
	ret


