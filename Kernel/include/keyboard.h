#include <stdint.h>
#include <naiveConsole.h>

extern uint8_t getKeyPressed();
extern uint8_t isKeyboardActive();
uint8_t getKey();
void putKey(uint8_t key);
void keyboard_handler();