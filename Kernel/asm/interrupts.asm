global asm_cli, asm_sti

global pic_master_mask, pic_slave_mask
global asm_syscall80_handler

global asm_irq00_handler, asm_irq01_handler

extern irq_dispatcher, syscall_dispatcher

SECTION .text


%macro push_state 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro pop_state 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

;handler de las interrupcion Hardware
%macro irq_handler 1
    push_state
    mov rdi,%1
    call irq_dispatcher

    ;signal pic EOI (End of Interrupt)
    mov al,0x20
    out 0x20, al

    pop_state
    iretq
%endmacro

; sys_id is stored in rax (hardcoded)
%macro syscall_handler 1
    ; push_state
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15

    mov r15, rax
    call syscall_dispatcher

    push rax

    ; signal pic EOI (End of Interrupt)
    mov al, 0x20
    out 0x20, al

    pop rax


    ; pop_state
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
    iretq
%endmacro

asm_cli:
    cli
    ret

asm_sti:
    sti
    ret

pic_master_mask:
    push rbp
    mov rbp, rsp

    mov ax, di
    out 0x21, al

    pop rbp
    retn

pic_slave_mask:
    push rbp
    mov rbp, rsp

    mov ax, di
    out 0x0A1, al

    pop rbp
    retn


;Timer interrupt(timer tick)
asm_irq00_handler:
    irq_handler 0

;Keyboard interrupt
asm_irq01_handler:
    irq_handler 1

; Syscall (id) interrupt
asm_syscall80_handler:
    syscall_handler 80