/******************************************************************************
 *
 * @file    colors.h
 *
 * @brief   Colors!!
 *
 * @author  Luca Pugliese                           <lpugliese@itba.edu.ar>
 * @author  Felipes Venturino                        <fventurino@itba.edu.ar>
 * @author  Uriel Sosa Vazquez                      <usosavazquez@itba.edu.ar>
 *
 ******************************************************************************/
#ifndef COLORS_H
#define COLORS_H

#include <stdint.h>

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb_t;

typedef uint32_t color_t;

#define COLOR_BLACK color(0, 0, 0)
#define COLOR_WHITE color(255, 255, 255)
#define COLOR_RED color(255, 0, 0)
#define COLOR_GREEN color(0, 255, 0)
#define COLOR_BLUE color(0, 0, 255)
#define COLOR_YELLOW color(255, 255, 0)
#define COLOR_CYAN color(0, 255, 255)
#define COLOR_MAGENTA color(255, 0, 255)

// Pass from r,g,b value to a color_t (hex value)
uint32_t color(uint32_t r, uint32_t g, uint32_t b);

#endif