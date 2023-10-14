#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t printf_color(const char *fmt, uint64_t fgcolor, uint64_t bgcolor, ...) {
    uint64_t i = 0;
    while (fmt[i]) {
        if (fmt[i] == '%') {
            switch (fmt[i + 1]) {
                case 'd':
                    // print decimal
                    break;
                case 'x':
                    // print hex
                    break;
                case 's':
                    // print string
                    break;
                default:
                    // print char
                    break;
            }
            i++;
        } else {
            putchar_color(fmt[i], fgcolor, bgcolor);
            // print char
        }
        i++;
    }

    return i;

}
uint64_t printf(const char *fmt, ...) {
    return printf_color(fmt, 0xFFFFFF, 0x000000);
}

