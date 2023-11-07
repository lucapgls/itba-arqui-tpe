#ifndef AMONGUS_H
#define AMONGUS_H

#include <stdint.h>
#include <colors.h>
#include <syscalls.h>

#define ROWS 32
#define COLS 127

void amongus(uint64_t startx, uint64_t starty);

static const char silence_art[][COLS];

#endif