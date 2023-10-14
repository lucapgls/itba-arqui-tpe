#ifndef STDIO_H
#define STDIO_H

#include <stdint.h>
#include <stdio.h>

uint64_t printf(const char* format, ...);
uint64_t printf_color(const char* format, uint64_t fgcolor, uint64_t bgcolor, ...);

#endif