GLOBAL read, write

write:
; test
    mov rdi, 1
    mov rsi, "Hola"
    mov rdx, 4
    ;
    mov rax, 1
    int 0x80
    ret

read:
    mov rax, 0
    int 0x80
    ret

