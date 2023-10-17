#include <keyboard.h>
#include <io.h>
#include <font.h>

#define BUFFER_SIZE 10

static uint8_t shift = 0;

static char buffer[BUFFER_SIZE] = {0};
static int8_t first_ptr = 0; // Points to the front of the buffer.
static int8_t last_ptr = 0;  // Points to the last element added.

static uint8_t key_pressed = 0;

void keyboard_handler()
{
    uint8_t key = get_key();
}

// Get the ascii value of the key pressed and detect if the shift was also pressed.
uint8_t get_key()
{
    char key = asm_get_key();
    if (key >= 0 && key <= KBD_LENGTH)
    {
        if (key == LSHIFT || key == RSHIFT)
        {
            shift = 1;
        }

        else if (key == RELEASE_LSHIFT || key == RELEASE_RSHIFT)
        {
            shift = 0;
        }

        key = kbd_codes[key][shift];
        add_to_buffer(key);

        // Print character (temp, to be displayed in shell) 
        //  putchar(key);


        return key;
    }

    return 'A';
}



void add_to_buffer(uint8_t key)
{
        // for circular buffer
    buffer[last_ptr++] = key;
    last_ptr %= BUFFER_SIZE;
    // if (key == '\n') {
    //     first_ptr = last_ptr;
    // }
}

uint64_t get_buffer(char *buff, uint64_t count)
{
    uint64_t i = 0;
    while (i < count) {
        buff[i++] = buffer[first_ptr++ % BUFFER_SIZE];
    }

    // "Limpio el buffer"
    first_ptr = 0;

    return i;
}


// Get the last input from the buffer and remove it from the buffer.
uint8_t get_last_input()
{
    if (last_ptr != 0) {
        uint8_t key = buffer[--last_ptr];

        return key;
    } else {
        return 0;
    }

}