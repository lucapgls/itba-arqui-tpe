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
uint64_t sys_random_number(int seed);
void draw(uint32_t color, uint64_t posx, uint64_t posy);
void sys_sleep(uint64_t millis);
char* sys_time();
void sys_sound(uint8_t freq, uint64_t duration);
void sys_hlt();
void sys_clear(uint32_t color);

void sys_writing_position(uint64_t x, uint64_t y);
void screen_info(uint64_t *width, uint64_t *height);
void font_size(int size);

void sys_registers();
void save_registers(uint64_t *stack);

#endif