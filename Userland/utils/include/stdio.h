#ifndef STDIO_H
#define STDIO_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <colors.h>

uint64_t printf_color(const char* format, uint32_t fgcolor, uint32_t bgcolor, ...);
int64_t gets(char *buff, uint64_t length);
// uint64_t scanf(const char* format, ...);

#define printf(fmt, ...) printf_color(fmt, COLOR_WHITE, COLOR_BLACK, ##__VA_ARGS__)


#endif