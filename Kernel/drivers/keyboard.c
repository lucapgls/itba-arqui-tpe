#include <keyboard.h>
#include <io.h>
#include <font.h>

#define BUFFER_SIZE 20

static uint8_t shift = 0;

static int8_t buffer[BUFFER_SIZE] = {0};
static int8_t buffer_ptr = 0, buffer_r_ptr = 0;

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

// Get the ascii value of the key pressed and detect if the shift was also pressed.
uint8_t get_key()
{
    uint8_t key;
    key = asm_get_key();
    if (key == LSHIFT || key == RSHIFT)
    {
        shift = 1;
    }
    else if (key == RELEASE_LSHIFT || key == RELEASE_RSHIFT)
    {
        shift = 0;
    }


    key = kbd_codes[key][shift];

    return key;
}

void keyboard_handler()
{

    uint8_t key = get_key();
    if (key > 0 && key < 255)
    {
        add_to_buffer(key);
        putchar(key);
    }

}

void add_to_buffer(uint8_t key)
{
    buffer[buffer_ptr++] = key;
    // if (key == '\b')
    // {
    //     if (buffer_ptr > 0)
    //     {
    //         buffer_ptr--;
    //     }
    // }

   

    if (buffer_ptr >= BUFFER_SIZE)
    {
        buffer_ptr = 0;
    }

    // buffer[buffer_ptr] = key;
}

uint64_t get_buffer(char *buff, uint64_t count)
{
    uint64_t i = 0;
    while (i < count) {
        buff[i++] = buffer[buffer_r_ptr++];
        if (buff[i-1] == '\n') {
            buffer_r_ptr++;
            break;
        }
    }
    return i;
}

// Get the last input from the buffer and remove it from the buffer.
uint8_t get_last_input()
{
    uint8_t key = buffer[buffer_ptr-1];
    if (key != 0)
    {
        buffer[buffer_ptr] = 0;
        buffer_ptr++;
        if (buffer_ptr == BUFFER_SIZE)
        {
            buffer_ptr = 0;
        }
    }
    return key;
}