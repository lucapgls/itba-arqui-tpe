#ifndef IO_H
#define IO_H 
#include <stdint.h>
#include <syscalls.h>

uint64_t printf(const char *fmt, ...);
uint64_t printf_color(const char * str, uint64_t fgcolor, uint64_t bgcolor);
uint64_t scanf(const char *fmt, ...);
#endif