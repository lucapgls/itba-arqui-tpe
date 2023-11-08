/******************************************************************************
 *
 * @file    syscalls.h
 *
 * @brief   Handle system calls (Kernel side) 
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
 * @name sys_write
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
uint64_t sys_write(uint8_t fd, const char *buffer, uint64_t count, uint64_t fgcolor, uint64_t bgcolor);

/*
 * @name sys_read
 *
 * @brief Reads from the buffer into the file descriptor passed as parameter.
 * @param fd File descriptor.
 * @param buffer Buffer to be modified.
 * @param count Amount of bytes to be read.
 */
char *sys_read(uint8_t fd, char *buffer, uint64_t count);


/* 
 * @name pid
 *
 * @brief Returns the current process id. (WIP)
 */
uint64_t pid();

/*
 * @name sys_exec
 *
 * @brief Executes a program. (WIP)
 */
void sys_exec();

/*
 * @name sys_ticks
 * @brief Returns the current system tick count. 
 */
uint64_t sys_ticks();

/*
 * @name sys_read_char
 * @brief Returns the last character read from the keyboard.
 */
char sys_read_char();

/*
 * @name sys_seconds
 * @brief Returns the current system time in seconds.
 */
uint64_t sys_seconds();



/*
 * @name sys_random_number
 * @brief Returns a random number based of the seed passed as parameter.
 */
uint64_t sys_random_number(int seed);

/*
 * @name draw
 * @brief Draws a pixel (8x8) in the position passed as parameter.
 */
void draw(uint32_t color, uint64_t posx, uint64_t posy);

void sys_sleep(uint64_t millis);

/*
 * @name sys_time
 *
 * @brief Returns the current system time in format
 * @returns char* with the current system time. (HH:MM:SS)
 * 
 */
char* sys_time();

/*
 * @name sys_sound
 * @brief Plays a sound with the frequency and duration passed as parameters.
 *
 * @param freq Frequency of the sound.
 * @param duration Duration of the sound.
 * 
 */
void sys_sound(uint8_t freq, uint64_t duration);

/*
 * @name sys_hlt
 *
 * @brief Halts the system until an interrupt is received.
 */
void sys_hlt();

/*
 * @name sys_clear
 *
 * @brief Clears the screen with the color passed as parameter.
 * 
 * @param color Color to clear the screen.
 */
void sys_clear(uint32_t color);

/*
 * @name sys_writing_position
 *
 * @brief Sets the writing position to the coordinates passed as parameters.
 * 
 * @param x X coordinate.
 * @param y Y coordinate.
 * 
 */
void sys_writing_position(uint64_t x, uint64_t y);

/*
 * @name screen_info
 *
 * @brief Returns the screen width and height.
 * 
 * @param width Pointer to the width variable.
 * @param height Pointer to the height variable.
 */
void screen_info(uint64_t *width, uint64_t *height);

/*
 * @name font_size
 *
 * @brief Sets the font size to the size passed as parameter. 
 * 
 * @param size Size of the font.
 */
void font_size(int size);

/*
 * @name sys_registers
 *
 * @brief Prints the registers of the last time captured.
 * 
 */
void sys_registers();

/*
 * @name save_registers
 *
 * @brief Captures the values of registers at this time.
 */
void save_registers(uint64_t *stack);

#endif