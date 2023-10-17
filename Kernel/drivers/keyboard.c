#include <keyboard.h>
#include <io.h>
#include <font.h>

#define BUFFER_SIZE 10

static uint8_t shift = 0;

static uint8_t buffer[BUFFER_SIZE] = {0};
static int8_t first_ptr = 0; // Points to the front of the buffer.
static int8_t last_ptr = 0;  // Points to the last element added.

static int8_t buffer_count = 0; // to keep count of how many keys are in the buffer

static uint8_t key_pressed = 0;

void keyboard_handler()
{
    uint8_t key = get_key();
}

// Get the ascii value of the key pressed and detect if the shift was also pressed.
uint8_t get_key()
{
    uint8_t key = asm_get_key();
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
        buffer[last_ptr++] = key;

        // for circular buffer
        first_ptr %= BUFFER_SIZE;
        last_ptr %= BUFFER_SIZE;


        buffer_count++;
        if (buffer_count == BUFFER_SIZE) {
            // first_ptr = 0;
            // last_ptr = 0;
            buffer_count = 0;
        }

        // add to buffer


        // ignore pressed keys
        // key_pressed = !key_pressed;

        putchar(buffer[last_ptr]);

        // if (key == '\n') {
        //     printf("Enter\n");
        //     printf((char) buffer);
        // }

        return key;
    }

    return 0;
}



void add_to_buffer(uint8_t key)
{
    // if (key == '\n') {
    //     buffer_r_ptr = 0;  // Reset the read pointer
    //     buffer_ptr = 0;    // Reset the write pointer
    // } else if (buffer_ptr < BUFFER_SIZE) {
    //     buffer[buffer_ptr++] = key;
    // } else {
    //     buffer_ptr = 0;
    //     buffer_r_ptr = 0;  // Reset the read pointer

    // }
}

uint64_t get_buffer(char *buff, uint64_t count)
{
    uint64_t i = 0;
    while (i < count) {
        if (first_ptr >= last_ptr) {
            break;
        }

        buff[i++] = buffer[first_ptr++];
    }
    //     if (first_ptr == BUFFER_SIZE){
    //         first_ptr = 0;
    //     }
    //     if (first_ptr < last_ptr) {

    //     char c = buffer[first_ptr++];
    //     if (c != 0)
    //         buff[i++] = c;
    //     }

    //     // if (c == '\n') {
    //     //     // Terminate the string at newline and reset the buffer
    //     //     buff[i] = '\0';
    //     //     bu = 0;
    //     //     buffer_ptr = 0;
    //     //     break;
    //     // }
    // }

    // // "Limpio el buffer"
    // first_ptr = 0;
    // last_ptr = 0;
    // key_pressed = 0;

    return i;
}


uint8_t get_first_input()
{
    if (first_ptr < last_ptr) {
        uint8_t key = buffer[first_ptr];
        // putchar(key);
        first_ptr++;
        return key;
    } else {
        return 0;
    }

}

// Get the last input from the buffer and remove it from the buffer.
uint8_t get_last_input()
{

    if (last_ptr != 0) {
        uint8_t key = buffer[last_ptr-1];
        // putchar(last_ptr + '0');
        // putchar(key);
        last_ptr++;


        return key;
    } else {
        return 0;
    }

}