#include <stdint.h>

void timer_handler();

uint64_t seconds_elapsed();
uint64_t ticks_elapsed();
uint64_t sleep(uint64_t ms);
extern void asm_hlt();