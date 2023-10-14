#include <naiveConsole.h>
#include "syscalls.h"
#include "keyboard.h"
#include "io.h"



enum syscalls {
    SYS_WRITE = 1, 
    SYS_READ,
    SYS_PID,
    SYS_EXEC,
    SYS_CREATE_PROCESS,
    SYS_KILL_PROCESS,
};

uint64_t syscall_dispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r9, uint64_t r8) {
    switch (rdi) {
        case SYS_WRITE:
            sys_write(rdx, (char *)rsi , r10);
            break;
        case SYS_READ:
            sys_read();
            break;
        case SYS_PID:
            pid();
            break;
        case SYS_EXEC:
            sys_exec();
            break;
    }
}

void sys_write(uint8_t fd, const char *buffer, uint64_t count)
{
    if (fd == 1) {
        printf(buffer);
    }
        // ncPrint(buffer);
    else if (fd == 2)
        printf_color(buffer, 0xFF, 0x40);
        // ncPrintColor(buffer, 0xFF, 0x40);

}

char sys_read(){
    char c = get_last_input();
    putchar(c);
    return c;
}


uint64_t pid() {
    return 0;
}
void sys_exec(){

}