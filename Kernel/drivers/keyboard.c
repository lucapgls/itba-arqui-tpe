#include <keyboard.h>

static uint8_t shift = 0;

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

// Keyboard codes
static const uint8_t keyboardCodes[][2] = {
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



// Get the ascii value of the key pressed and detect if the shift was also pressed.
uint8_t getKey() {
    uint8_t key;
    while (isKeyboardActive()) {
        key = getKeyPressed();
        if (key == LSHIFT || key == RSHIFT) {
            shift = 1;
        } else if (key == RELEASE_LSHIFT || key == RELEASE_RSHIFT) {
            shift = 0;
        }
        
        key = keyboardCodes[key][shift];
        return key;
    }
    return 0;
}

void putKey(uint8_t key)
{

    switch (key)
    {
    case '\b':
        ncBackspace();
        return;
    case '\n':
        ncNewline();
        return;
    case '\t':
        ncPrint("    ");
        return;
    }

    // temp
    if (key > 2 && key < 250)
    {
        // ncPrintChar(key);
        return;
    }

}

void keyboard_handler() {

    // temp
    putKey(getKey());
}