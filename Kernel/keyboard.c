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

void putKey()
{

    // while (1)
    {
        char key = getKeyPressed();

        ncPrint(key);
        switch (keyboardCodes[key][0])
        {
        case '\b':
            // ncPrintBackspace();
            break;
        case '\n':
            ncNewline();
            break;
        default:
            ncPrintChar(keyboardCodes[key][0]);
            break;
        }

        // falta shift para acceder al [1]
        // ncPrint(keyboardCodes[key][0]);
    }
}