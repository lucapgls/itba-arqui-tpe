#include "io.h"
#include <video.h>

// starting position
static uint64_t x = 0;
static uint64_t y = 0;

uint64_t printf(const char * str, ...) {
    return printf_color(str, 0xFFFFFF, 0x000000);
}

uint64_t printf_color(const char * str, uint64_t fgcolor, uint64_t bgcolor) {
  int i = 0;
  uint64_t tempx, tempy;
  while (str[i])
  {

    switch (str[i]) {
        case '\n':
            x = -i * 8 - 8; // set the x position so x + i starts in 0
            y += 12 + 4; // 12 is baseline, 4 is padding
            i++; // skip the not representable char
            break;
    }

    tempx = x + i * 8;
    put_char_at(str[i], tempx, y, fgcolor, bgcolor);
    i++;
  }   
    x = x + i * 8; // 8 is FONT_WIDTH
    return i;
}

