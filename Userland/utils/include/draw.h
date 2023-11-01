#ifndef DRAW_H
#define DRAW_H

#include <colors.h>

#define PIXEL 8

void draw_line(color_t color, uint64_t startx, uint64_t starty, uint64_t endx, uint64_t endy);
void draw_bitmap(color_t color, char *bitmap[], uint16_t rows, uint16_t cols, uint64_t startx, uint64_t starty);

#endif