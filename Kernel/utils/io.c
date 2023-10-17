#include "io.h"
#include <video.h>

// starting position
static uint64_t x = 0;
static uint64_t y = 16;

uint64_t printf(const char * str, ...) {
    return printf_color(str, 0xFFFFFF, 0x000000);
}

uint64_t printf_color(const char * str, uint64_t fgcolor, uint64_t bgcolor) {
  int i = 0;
  uint64_t tempx, tempy;
  while (str[i])
  {

    putchar_color(str[i++], fgcolor, bgcolor);

    // // tempx = x + i * 8;
    // put_char_at(str[i], &x, &y, fgcolor, bgcolor);
    // i++;
  }   
    // x = x + i * 8; // 8 is FONT_WIDTH
    return i;
}

void putchar_color(char c, uint64_t fgcolor, uint64_t bgcolor) 
{
    switch(c) {
        case '\n':
            x = 0;
            y += 16;
            break;
        case '\b':
            delete_char(&x, &y, fgcolor, bgcolor);
            break;
        default:
            put_char_at(c, &x, &y, fgcolor, bgcolor);
            break;
    }
}

void putchar(char c) 
{
    putchar_color(c, 0xFFFFFF, 0x000000);
}


// scanf("num1: %d num2: %d", &num1, &num2) = 2
uint64_t scanf(const char *fmt, ...) {

    printf("InvalArgumentException");
    while(*fmt){
      if(*fmt == '%') {
        
      }
    }
}
