#include <stdint.h>
#include <naiveConsole.h>

extern uint8_t asm_get_key();
uint8_t get_key();
void keyboard_handler();
void add_to_buffer(uint8_t key);
uint8_t get_last_input();
uint64_t get_buffer(char *buff, uint64_t count);