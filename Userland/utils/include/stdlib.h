/******************************************************************************
 *
 * @file    stdlib.h
 *
 * @brief   Standard library functions. (Similar, but primitive, to C stdlib.h)
 *
 * @author  Luca Pugliese                           <lpugliese@itba.edu.ar>
 * @author  Felipes Venturino                        <fventurino@itba.edu.ar>
 * @author  Uriel Sosa Vazquez                      <usosavazquez@itba.edu.ar>
 *
 ******************************************************************************/
#ifndef STDLIB_H
#define STDLIB_H

#include <stdint.h>

#define NULL ((void*)0)


void putchar_color(char c, uint64_t fgcolor, uint64_t bgcolor);
void putchar(char c);


// Read from keyboard a string of length characters
int64_t gets(char *buff, uint64_t length);
// Read a character
uint8_t getchar();

// Integer to Array
void itoa(uint64_t number, char* buff);

// Array to integer
uint64_t atoi(char* str);

#endif