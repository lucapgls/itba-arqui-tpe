GLOBAL read, write, random, read_char, draw, time



read:
    mov rax, 0
    int 0x80
    ret

write:
    mov rax, 1
    int 0x80
    ret

random:
    mov rax, 6
    int 0x80
    ret

read_char:
    mov rax, 7
    int 0x80
    ret

draw:
    mov rax, 8
    int 0x80
    ret

time:
    mov rax, 9
    int 0x80
    ret