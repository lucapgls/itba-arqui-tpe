#ifndef FONT_H
#define FONT_H
#include <stdint.h>

#define FONT_WIDTH 8
#define FONT_HEIGHT 16

uint8_t *get_char_bitmap(char c);
#endif