#ifndef STDLIB_H
#define STDLIB_H

#include <stdint.h>

#define NULL ((void*)0);
void putchar_color(char c, uint64_t fgcolor, uint64_t bgcolor);
void putchar(char c);
int64_t gets(char *buff, uint64_t length);
uint8_t getchar();
void itoa(uint64_t number, char* buff);
uint64_t atoi(char* str);

#endif