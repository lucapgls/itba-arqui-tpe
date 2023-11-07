#ifndef SYSCALLS_H_
#define SYSCALLS_H_
#include <stdint.h>

extern uint64_t write(uint8_t fd, const char *buffer, uint64_t count, uint64_t fgcolor, uint64_t bgcolor);

extern uint8_t * read(uint8_t fd, char *buffer, uint64_t count);
extern uint8_t read_char();

extern uint64_t random(int seed);

extern void draw(uint32_t color, uint64_t posx, uint64_t posy);
extern char *time();
extern uint64_t sleep(uint64_t millis);
extern void sound(uint64_t freq, uint64_t duration);
extern void hlt();
extern void clear(uint32_t color);
extern void writing_pos(uint64_t x, uint64_t y);
extern void screen_info(uint64_t *width, uint64_t *height);
extern void font_size(int size);
extern void sys_registers();
#endif