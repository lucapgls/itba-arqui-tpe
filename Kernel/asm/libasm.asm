GLOBAL cpuVendor
GLOBAL rtcTime
GLOBAL getKeyPressed
GLOBAL isKeyboardActive

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

isKeyboardActive:
	push rbp
	mov rbp, rsp

	mov rax, 0
	in al, 0x64
	and al, 0x01

	leave
	ret

getKeyPressed:
	push rbp
	mov rbp, rsp

	mov rax, 0
	in al, 0x60

	leave
	ret