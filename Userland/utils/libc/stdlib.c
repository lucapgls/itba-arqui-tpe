#include <stdlib.h>
#include <stdint.h>
#include <syscalls.h>


void putchar(char c){
     putchar_color(c, 0xFFFFFF, 0x000000);
}

void putchar_color(char c, uint64_t fgcolor, uint64_t bgcolor) 
{
   write(1, c, 1, fgcolor, bgcolor);
}

uint64_t strlen(char* buff){
    uint64_t ans = 0;
    while(buff[ans] != 0)
        ans++;
    return ans;
}


uint8_t getchar(uint8_t* c) {
    return read(0, c, 1);
}