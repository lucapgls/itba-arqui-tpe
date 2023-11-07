#ifndef SOUND_H
#define SOUND_H
#include <stdint.h>

extern void asm_start_sound(uint32_t freq);
extern void asm_end_sound();


// duration in seconds
void sound(uint8_t freq, uint64_t duration);
void beep();
#endif