#include <io.h>
#include <lib.h>
#include <naiveConsole.h>
#include <stdint.h>
#include <time.h>

// Each tick will be 1/18 of a second (51ms)
static unsigned long ticks = 0;

void timer_handler() {
    ticks++;
}

uint64_t seconds_elapsed() {
    return ticks / 18;
}

uint64_t ticks_elapsed() {
    return ticks;
}

uint64_t sleep(uint64_t millis) {
    uint64_t start = ticks;
    while (ticks - start < millis / 51) {
        asm_hlt();
    }
    return 0;
}

void hlt() {
    asm_hlt();
}