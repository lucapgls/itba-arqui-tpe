#include <string.h>
#include <stdint.h>


int8_t strcmp(const char* s1, const char* s2) {
    while(*s1 == *s2 && *s1 != '\0'){
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

uint64_t strlen(char* buff)
{
    uint64_t ans = 0;
    while(buff[ans] != 0)
        ans++;
    return ans;
}