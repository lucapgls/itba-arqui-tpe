#include <stdlib.h>
#include <stdint.h>
#include <syscalls.h>
#include <stdio.h>



void putchar(char c)
{
     putchar_color(c, 0xFFFFFF, 0x000000);
}

void putchar_color(char c, uint64_t fgcolor, uint64_t bgcolor) 
{
   write(1, &c, 1, fgcolor, bgcolor);
}

uint8_t getchar() 
{
    return read_char();
}

int64_t gets(char *buff, uint64_t length) 
{
    uint64_t i = 0;
    char c;
    do {
        c = getchar();
        if (c >= 0x20 && c <= 0x7F) {
            buff[i] = c;
            putchar(buff[i++]);
        }

        if (c == '\n') {
            buff[i] = '\0';
        }
        if (c == '\b') {
            if (i > 0) {
                i--;
                putchar('\b');
            }
        }
    }
    while (i < length && c != '\n');

    
    // read(0, buff, length);
    return i;
    // return read(1, buff, length);
}

static void reverse_str(char str[], int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

uint64_t atoi(char* str) 
{
    uint64_t ans = 0;
    
    int i = 0;
    uint8_t sign = 1;

    if (str[i] == '-') {
        sign = -1;
        i++;
    }

    while (str[i] >= '0' && str[i] <= '9') {
        ans = ans * 10 + (str[i] - '0');
        i++;
    }
    return ans * sign;
}

void itoa(uint64_t number, char* buff) 
{
    int i = 0;
    int is_neg = 0;

    if (number == 0) {
        buff[i++] = '0';
        buff[i] = '\0';
        return;
    }

    // Handle negative numbers
    if (number < 0) {
        is_neg= 1;
        number = -number;
    }

    while (number != 0) {
        int digit = number % 10;
        buff[i++] = '0' + digit;
        number = number / 10;
    }

    if (is_neg) {
        buff[i++] = '-';
    }

    buff[i] = '\0';

    reverse_str(buff, i);
    
}

