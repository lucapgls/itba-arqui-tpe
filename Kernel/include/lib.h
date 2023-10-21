#ifndef LIB_H
#define LIB_H

#include <stdint.h>

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);

extern char *cpuVendor(char *result);


extern uint8_t rtcTime(uint8_t option);

uint8_t getSeconds();
uint8_t getMinutes();
uint8_t getHours();

void itoa(char* str, int num, int width);

// Returns string with time format.
void getTime();
// temp
extern uint64_t test_write(uint8_t fd, const char *buffer, uint64_t count);


//Random
uint64_t get_random_number();


#endif