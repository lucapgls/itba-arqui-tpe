/******************************************************************************
 *
 * @file    sound.h
 *
 * @brief   Sound functions to play sounds.
 *
 * @author  Luca Pugliese                           <lpugliese@itba.edu.ar>
 * @author  Felipes Venturino                        <fventurino@itba.edu.ar>
 * @author  Uriel Sosa Vazquez                      <usosavazquez@itba.edu.ar>
 *
 ******************************************************************************/

#ifndef SOUND_H
#define SOUND_H
#include <stdint.h>

// Setup the sound with frequency.
extern void asm_start_sound(uint32_t freq);

// Stop the sound.
extern void asm_end_sound();


/*
 * @name sound
 *
 * @brief Plays a sound with the frequency and duration passed as parameters.
 * 
 * @param freq Frequency of the sound.
 * @param duration Duration of the sound.
 */
void sound(uint8_t freq, uint64_t duration);

// Play a beep sound.
void beep();
#endif