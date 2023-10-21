#include <time.h>
#include <stdint.h>
#include <naiveConsole.h>
#include <io.h>

// Each tick will be 1/18 of a second (51ms)
static unsigned long ticks = 0;

void timer_handler() {
    ticks++;

    // if (ticks % (5 * 18) == 0) {
    //     // printf("5 seconds have passed\n");
    // }
}

uint64_t seconds_elapsed() {
    return ticks / 18;
}

uint64_t ticks_elapsed() {
    return ticks;
}

void sleep(uint64_t time){
    uint64_t last = ticks;
    while(ticks - last < time)
        asm_hlt();
}