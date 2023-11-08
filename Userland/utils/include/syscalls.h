/******************************************************************************
 *
 * @file    syscalls.h
 *
 * @brief   Handle system calls (Userland side) 
 *
 * @author  Luca Pugliese                           <lpugliese@itba.edu.ar>
 * @author  Felipes Venturino                        <fventurino@itba.edu.ar>
 * @author  Uriel Sosa Vazquez                      <usosavazquez@itba.edu.ar>
 *
 ******************************************************************************/

#ifndef SYSCALLS_H
#define SYSCALLS_H
#include <stdint.h>

/*
 * @name write
 *
 * @brief Writes into the file descriptor the buffer passed as parameter.
 *
 * @param fd File descriptor.
 * @param buffer Buffer to be written.
 * @param count Amount of bytes to be written.
 * @param fgcolor Foreground color.
 * @param bgcolor Background color.
 * 
 */
extern uint64_t write(uint8_t fd, const char *buffer, uint64_t count, uint64_t fgcolor, uint64_t bgcolor);

/*
 * @name read
 *
 * @brief Reads from the buffer into the file descriptor passed as parameter.
 * @param fd File descriptor.
 * @param buffer Buffer to be modified.
 * @param count Amount of bytes to be read.
 */
extern uint8_t * read(uint8_t fd, char *buffer, uint64_t count);


/*
 * @name read_char
 * @brief Returns the last character read from the keyboard.
 */
extern uint8_t read_char();


/*
 * @name sys_random_number
 * @brief Returns a random number based of the seed passed as parameter.
 */
extern uint64_t random(int seed);

/*
 * @name draw
 * @brief Draws a pixel (8x8) in the position passed as parameter.
 */
extern void draw(uint32_t color, uint64_t posx, uint64_t posy);

/*
 * @name time
 * @brief Returns the current time (HH:MM:SS).
 */
extern char *time();

/*
 * @name sleep
 * @brief Sleeps the system for the amount of milliseconds passed as parameter.
 * 
 */
extern uint64_t sleep(uint64_t millis);

/*
 * @name sound
 * @brief Plays a sound with the frequency and duration passed as parameter.
 * @param freq Frequency of the sound.
 * @param duration Duration of the sound.
 * 
 */
extern void sound(uint64_t freq, uint64_t duration);

/*
 * @name hlt
 * @brief Halts the system until an interrupt is received.
 *
 */
extern void hlt();

/*
 * @name clear
 * @brief Clears the screen with the color passed as parameter.
 * 
 */
extern void clear(uint32_t color);

/*
 * @name writing_pos
 * @brief Sets the position of the next character(s) to be written.
 * 
 */
extern void writing_pos(uint64_t x, uint64_t y);

/*
 * @name screen_info
 * @brief Returns the screen width and height.
 * 
 * @param width Pointer to the width variable.
 * @param height Pointer to the height variable.
 * 
 */
extern void screen_info(uint64_t *width, uint64_t *height);

/* 
 * @name font_size
 * @brief Sets the font size.
 * 
 */
extern void font_size(int size);

/*
 * @name sys_registers
 * @brief Prints the registers.
 * 
 */
extern void sys_registers();


extern void test_exc_zero();

extern void test_exc_invalid_opcode();
#endif