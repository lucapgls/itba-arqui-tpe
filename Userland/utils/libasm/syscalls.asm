GLOBAL read, write



write:
    mov rax, 1
    int 0x80
    ret

read:
    mov rax, 0
    int 0x80
    ret


