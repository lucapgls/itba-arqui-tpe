#include <stdint.h>

uint64_t sys_write(uint8_t fd, const char *buffer, uint64_t count);
char sys_read();
uint64_t pid();
void sys_exec();
uint64_t sys_ticks();
uint64_t sys_seconds();