#include <naiveConsole.h>
#include "syscalls.h"
#include "keyboard.h"
#include "io.h"

uint64_t syscall_dispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r9, uint64_t r8) {
    switch (rdi) {
        case 1:
            sys_write(rdx, (char *)rsi , r10);
            break;
        case 2:
            sys_read();

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
    return get_key();
}
