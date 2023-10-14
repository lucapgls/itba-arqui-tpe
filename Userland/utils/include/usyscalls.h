#ifndef USYSCALLS_H_
#define USYSCALLS_H_
#include <stdint.h>

extern uint64_t write(uint8_t fd, const char *buffer, uint64_t count);
#endif