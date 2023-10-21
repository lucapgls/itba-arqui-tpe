#include <stdint.h>

extern void asm_hlt();

void timer_handler();

uint64_t seconds_elapsed();
uint64_t ticks_elapsed();
<<<<<<< HEAD
void sleep(uint64_t time);
=======
uint64_t sleep(uint64_t ms);
>>>>>>> 305b30343a68c79045518789dd09fd99a852a2b8
