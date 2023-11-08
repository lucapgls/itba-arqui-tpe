/******************************************************************************
 *
 * @file    draw.h
 *
 * @brief   Draw functions.
 *
 * @author  Luca Pugliese                           <lpugliese@itba.edu.ar>
 * @author  Felipes Venturino                        <fventurino@itba.edu.ar>
 * @author  Uriel Sosa Vazquez                      <usosavazquez@itba.edu.ar>
 *
 ******************************************************************************/
#ifndef DRAW_H
#define DRAW_H

#include <colors.h>

#define PIXELSIZE 8

void draw_pixel(color_t color, uint16_t size, uint64_t x, uint64_t y);
void draw_rectangle(color_t color, uint16_t size, uint64_t x, uint64_t y);
void draw_line(color_t color, uint64_t startx, uint64_t starty, uint64_t endx, uint64_t endy);
void draw_bitmap(color_t color, char *bitmap[], uint16_t rows, uint16_t cols, uint64_t startx, uint64_t starty);

#endif