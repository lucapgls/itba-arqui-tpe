#include <stdint.h>

extern void asm_hlt();

void timer_handler();

uint64_t seconds_elapsed();
uint64_t ticks_elapsed();
void sleep(uint64_t time);