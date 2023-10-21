#include <time.h>
#include <stdint.h>
#include <naiveConsole.h>
#include <io.h>
#include <lib.h>

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

<<<<<<< HEAD
void sleep(uint64_t time){
    uint64_t last = ticks;
    while(ticks - last < time)
        asm_hlt();
=======
uint64_t sleep(uint64_t millis) {
    uint64_t start = ticks;
    while (ticks - start < millis / 51) {
        asm_hlt();
    }
    return 0;
>>>>>>> 305b30343a68c79045518789dd09fd99a852a2b8
}