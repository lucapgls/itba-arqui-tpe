#include <time.h>
#include <stdint.h>
#include <naiveConsole.h>

static unsigned long ticks = 0;

void timer_handler() {
    ticks++;

    if (ticks % (5 * 18) == 0) {
        ncPrint("5 seconds have passed\n");
    }
}

uint64_t seconds_elapsed() {
    return ticks / 18;
}