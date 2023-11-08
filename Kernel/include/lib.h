#ifndef LIB_H
#define LIB_H

#include <stdint.h>

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);

extern char *cpuVendor(char *result);


extern uint8_t rtcTime(uint8_t option);

uint32_t getSeconds();
uint32_t getMinutes();
uint32_t getHours();

void itoa(char* str, int num, int width);

// Returns string with time format.
void getTime();

//Random
uint64_t get_random_number(int seed);

extern void outb(unsigned short port, unsigned char val);
extern uint8_t inb(unsigned short port);

#endif