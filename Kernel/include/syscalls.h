#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stdint.h>

uint64_t sys_write(uint8_t fd, const char *buffer, uint64_t count, uint64_t fgcolor, uint64_t bgcolor);
char *sys_read(uint8_t fd, char *buffer, uint64_t count);
uint64_t pid();
void sys_exec();
uint64_t sys_ticks();
char sys_read_char();
uint64_t sys_seconds();
uint64_t sys_random_number();
void draw(uint32_t color, uint64_t posx, uint64_t posy);
char *sys_time();
#endif