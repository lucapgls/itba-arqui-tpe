#ifndef __VIDEO_H__
#define __VIDEO_H__

#include <stdint.h>

void put_char_at(unsigned char c, uint64_t x, uint64_t y, uint64_t fgcolor, uint64_t bgcolor);
void draw_cursor(uint64_t x, uint64_t y, uint64_t fgcolor, uint64_t bgcolor);
void draw_backspace(uint64_t x, uint64_t y, uint64_t fgcolor, uint64_t bgcolor);

void put_pixel(uint32_t hexColor, uint64_t x, uint64_t y);

#endif