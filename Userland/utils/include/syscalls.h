#ifndef SYSCALLS_H_
#define SYSCALLS_H_
#include <stdint.h>

extern uint64_t write(uint8_t fd, const char *buffer, uint64_t count, uint64_t fgcolor, uint64_t bgcolor);

extern uint8_t * read(uint8_t fd, char *buffer, uint64_t count);
extern uint8_t read_char();

extern uint64_t random();
#endif