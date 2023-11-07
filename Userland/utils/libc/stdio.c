#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <colors.h>

void scanf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    for (uint64_t i = 0; fmt[i]; i++) {
        if (fmt[i] == '%') {
            switch (fmt[++i]) {
            case 'd':;
                // max length of int to be read is 24 (arbitrary)
                char buffer[24];
                gets(buffer, 24);
                int val = atoi(buffer);
                int *aux = va_arg(args, int *);
                *aux = val;
                break;
            case 's':
                gets(va_arg(args, char *), 100);
                break;
            case 'c':
                gets(va_arg(args, char), 1);
                break;
            default:
                break;
            }
        } else {
            putchar(fmt[i]);
        }
    }
    va_end(args);
}

static void print_str(const char *s, uint32_t fgcolor, uint32_t bgcolor) {

    uint64_t i = 0;
    while (s[i]) {
        putchar_color(s[i++], fgcolor, bgcolor);
    }
}

uint64_t printf_color(const char *fmt, uint32_t fgcolor, uint32_t bgcolor, ...) {
    va_list args;
    va_start(args, fmt);

    uint64_t i = 0;
    while (fmt[i]) {
        if (fmt[i] == '%') {
            switch (fmt[++i]) {
            case 'd':;
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
        } else {
            putchar_color(fmt[i], fgcolor, bgcolor);
        }
        i++;
        va_end(args);
    }
    return i;
}
