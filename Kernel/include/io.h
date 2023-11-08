/******************************************************************************
 *
 * @file    io.h
 *
 * @brief   General Input/Output functions (Kernel-side).
 *
 * @author  Luca Pugliese                           <lpugliese@itba.edu.ar>
 * @author  Felipes Venturino                        <fventurino@itba.edu.ar>
 * @author  Uriel Sosa Vazquez                      <usosavazquez@itba.edu.ar>
 *
 ******************************************************************************/

#ifndef IO_H
#define IO_H 
#include <stdint.h>
#include <syscalls.h>


uint64_t printf(const char *fmt, ...);
uint64_t printf_color(const char * str, uint64_t fgcolor, uint64_t bgcolor);

void putchar(char c);
void putchar_color(char c, uint64_t fgcolor, uint64_t bgcolor);

// Set the writing position to a new position
void set_position(uint64_t new_x, uint64_t new_y);


// @deprecated (Use userland-side function from stdio)
uint64_t scanf(const char *fmt, ...);
#endif