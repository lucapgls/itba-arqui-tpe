#include <keyboard.h>

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
    uint8_t shift = 0;
    while (isKeyboardActive()) {
        key = getKeyPressed();
        if (key == 0x2A || key == 0x36) {
            shift = 1;
        }

        key = keyboardCodes[key][shift];

        return key;
    }
    return key;
}

void putKey(uint8_t key)
{

    switch (key)
    {
    case '\b':
        ncBackspace();
        break;
    case '\n':
        ncNewline();
        break;
    case '\t':
        ncPrint("    ");
        break;
    }

    // falta shift para acceder al [1]
    if (key != 0 || key != '\b' || key != '\n' || key != '\t')
    {
        ncPrint(key);
        return;
    }
    // setFgColor(0xFF);
    // setBgColor(0x00);
    // ncPrintDec(key);
    // ncNewline();
    // ncPrintChar(keyboardCodes[key][0]);
}