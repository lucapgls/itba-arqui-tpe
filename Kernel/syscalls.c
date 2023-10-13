#include <naiveConsole.h>
#include "syscalls.h"


uint64_t syscall_dispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r9, uint64_t r8) {
    switch (rdi) {
        case 1:
            sys_write(rdx, (char *)rsi , r10);
            break;

    }
}

void sys_write(uint8_t fd, const char *buffer, uint64_t count){
    if (fd == 1)
        ncPrint(buffer);
    else if (fd == 2)
        ncPrintColor(buffer, 0xFF, 0x40);
}

