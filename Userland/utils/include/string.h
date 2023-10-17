#ifndef STRING_H
#define STRING_H
#include <stdint.h>

int8_t str_cmp(const char* src, const char* tgt);
uint64_t  str_len(char* buff);
#endif