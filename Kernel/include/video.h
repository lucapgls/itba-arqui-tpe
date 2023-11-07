#ifndef __VIDEO_H__
#define __VIDEO_H__

#include <stdint.h>

//extern void scanf(char * fmt, ...);

void put_char_at(unsigned char c, uint64_t *x, uint64_t *y, uint64_t fgcolor, uint64_t bgcolor);
void draw_cursor(uint64_t x, uint64_t y, uint64_t fgcolor, uint64_t bgcolor);
void delete_char(uint64_t *x, uint64_t *y, uint64_t fgcolor, uint64_t bgcolor);

void clear_screen(uint32_t hexColor);
void put_pixel(uint32_t hexColor, uint64_t x, uint64_t y);

void video_fontsize(int newsize);
int get_width();
int get_height();
#endif