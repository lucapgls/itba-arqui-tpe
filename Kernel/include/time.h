/******************************************************************************
 *
 * @file    time.h
 *
 * @brief   Time related functions
 *
 * @author  Luca Pugliese                           <lpugliese@itba.edu.ar>
 * @author  Felipes Venturino                        <fventurino@itba.edu.ar>
 * @author  Uriel Sosa Vazquez                      <usosavazquez@itba.edu.ar>
 *
 ******************************************************************************/

#ifndef TIME_H
#define TIME_H
#include <stdint.h>


// Ticks every 51ms
void timer_handler();

// Returns the amount of seconds that have passed since the system booted.
uint64_t seconds_elapsed();

// Returns the amount of ticks that have passed since the system booted.
uint64_t ticks_elapsed();

// Sleeps for ms miliseconds
uint64_t sleep(uint64_t ms);

// Halts the system, waits until a interrupt is received
extern void asm_hlt();
void hlt();

#endif
