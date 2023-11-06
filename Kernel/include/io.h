#ifndef IO_H
#define IO_H 
#include <stdint.h>
#include <syscalls.h>

uint64_t printf(const char *fmt, ...);
uint64_t printf_color(const char * str, uint64_t fgcolor, uint64_t bgcolor);
void putchar(char c);
void putchar_color(char c, uint64_t fgcolor, uint64_t bgcolor);
void set_position(uint64_t new_x, uint64_t new_y);


// Returns number of variables read in input
uint64_t scanf(const char *fmt, ...);
#endif