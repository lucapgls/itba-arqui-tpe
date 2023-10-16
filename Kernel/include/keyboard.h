#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include <naiveConsole.h>

// Special keys
#define LSHIFT 0x2A
#define RSHIFT 0x36
#define RELEASE_LSHIFT LSHIFT + 128
#define RELEASE_RSHIFT RSHIFT + 128
#define CAPSLOCK 0x3A
#define ESC 0x01
#define CTRL 0x1D
#define ALT 0x38
#define F1 0x3B
#define F2 0x3C
#define F3 0x3D

#define KBD_LENGTH 57
// Keyboard codes
static const uint8_t kbd_codes[][2] = {
    {0, 0},
    {0, 0},
    {'1', '!'},
    {'2', '@'},
    {'3', '#'},
    {'4', '$'},
    {'5', '%'},
    {'6', '^'},
    {'7', '&'},
    {'8', '*'},
    {'9', '('},
    {'0', ')'},
    {'-', '_'},
    {'=', '+'},
    {'\b', '\b'},
    {'\t', '\t'},
    {'q', 'Q'},
    {'w', 'W'},
    {'e', 'E'},
    {'r', 'R'},
    {'t', 'T'},
    {'y', 'Y'},
    {'u', 'U'},
    {'i', 'I'},
    {'o', 'O'},
    {'p', 'P'},
    {'[', '{'},
    {']', '}'},
    {'\n', '\n'},
    {0, 0},
    {'a', 'A'},
    {'s', 'S'},
    {'d', 'D'},
    {'f', 'F'},
    {'g', 'G'},
    {'h', 'H'},
    {'j', 'J'},
    {'k', 'K'},
    {'l', 'L'},
    {';', ':'},
    {'\'', '\"'},
    {'`', '~'},
    {0, 0},
    {'\'', '|'},
    {'z', 'Z'},
    {'x', 'X'},
    {'c', 'C'},
    {'v', 'V'},
    {'b', 'B'},
    {'n', 'N'},
    {'m', 'M'},
    {',', '<'},
    {'.', '>'},
    {'/', '?'},
    {0, 0},
    {0, 0},
    {0, 0},
    {' ', ' '},
};

extern uint8_t asm_get_key();
uint8_t get_key();
void keyboard_handler();
void add_to_buffer(uint8_t key);
uint8_t get_last_input();
uint64_t get_buffer(char *buff, uint64_t count);
uint8_t get_first_input();

#endif