#include <colors.h>

static uint32_t color_to_hex(color_t color)
{
    return (color.r << 16) | (color.g << 8) | color.b;
}

uint32_t color(uint32_t r, uint32_t g, uint32_t b)
{
    color_t color;
    color.r = r;
    color.g = g;
    color.b = b;
    return color_to_hex(color);
}