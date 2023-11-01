#include <stdint.h>

extern void asm_hlt();

void timer_handler();

uint64_t seconds_elapsed();
uint64_t ticks_elapsed();
<<<<<<< HEAD
uint64_t sleep(uint64_t ms);
extern void asm_hlt();
=======
uint64_t sleep(uint64_t time);
>>>>>>> cf5d39fd5690deb936c6ca7165fa030de41f49d9
