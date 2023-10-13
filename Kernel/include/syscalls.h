#include <stdint.h>

void sys_write(uint8_t fd, const char *buffer, uint64_t count);
char sys_read(uint8_t * state);