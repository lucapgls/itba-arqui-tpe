#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>

#include <colors.h>


int64_t gets(char *buff, uint64_t length) 
{
    
    return read(1, buff, length);
}

uint64_t scanf(const char *fmt, ...) 
{
//   va_list args;
  int i = 0, j = 0, ret = 0;
//   va_start(vl, fmt);
//   while (fmt && fmt[i]) {
//     if (fmt[i] == '%') {
//       i++;
//       switch (fmt[i]) {
//       case 'c': {
//         *(char *)va_arg(args, char *) = buff[j];
//         j++;
//         ret++;
//         break;
//       }
//       case 'd': {
//         *(int64_t *)va_arg(args, int64_t *) = atoi(&buff[j], &out_loc, 10);
//         j += out_loc - &buff[j];
//         ret++;
//         break;
//       }
//     } else {
//       buff[j] = fmt[i];
//       j++;
//     }
//     i++;
//     }
//   }

//   va_end(args);

  return ret;

}

static void print_str(const char* s, uint32_t fgcolor, uint32_t bgcolor)
{

    uint64_t i = 0;
    while (s[i])
    {
        putchar_color(s[i++], fgcolor, bgcolor);
    }
}

uint64_t printf_color(const char *fmt, uint32_t fgcolor, uint32_t bgcolor, ...)
{
    va_list args;
    va_start(args, fmt);

    uint64_t i = 0;
    while (fmt[i])
    {
        if (fmt[i] == '%')
        {
            switch (fmt[++i])
            {
            case 'd':
                ; 
                char buff[20];
                itoa(va_arg(args, int), buff);
                print_str(buff, fgcolor, bgcolor);
                break;
            case 's':
                print_str(va_arg(args, char *), fgcolor, bgcolor);
                break;

            case '%':
                putchar_color('%', fgcolor, bgcolor);
                break;
            default:
                break;
            }
        }
        else
        {
            putchar_color(fmt[i], fgcolor, bgcolor);
        }
        i++;
        va_end(args);
    }
    return i;
}
