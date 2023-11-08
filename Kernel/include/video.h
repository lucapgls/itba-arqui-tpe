/******************************************************************************
 *
 * @file    video.h
 *
 * @brief   Video functions to draw on screen while in video mode.
 *
 * @author  Luca Pugliese                           <lpugliese@itba.edu.ar>
 * @author  Felipes Venturino                        <fventurino@itba.edu.ar>
 * @author  Uriel Sosa Vazquez                      <usosavazquez@itba.edu.ar>
 *
 ******************************************************************************/

#ifndef VIDEO_H__
#define VIDEO_H__

#include <stdint.h>


// Write a character to the screen
void put_char_at(unsigned char c, uint64_t *x, uint64_t *y, uint64_t fgcolor, uint64_t bgcolor);

// Remove last character from the screen
void delete_char(uint64_t *x, uint64_t *y, uint64_t fgcolor, uint64_t bgcolor);

// Fill the whole screen with a color
void clear_screen(uint32_t hexColor);

// Put a pixel in position (pixel size is 1x1)
void put_pixel(uint32_t hexColor, uint64_t x, uint64_t y);

// Set de font size for the draweable characters
void video_fontsize(int newsize);

// Screen information (width and height)
int get_width();
int get_height();

#endif