#include <stdint.h>
#include <time.h>
#include <keyboard.h>

enum irq{
    TIMER = 0, KEYBOARD
};

void irq_dispatcher(uint64_t irq) {
    switch(irq) 
    {
        case TIMER: {
            timer_handler();
                break;
        } 
        case KEYBOARD: {
            keyboard_handler();
                break;
        }
    }
}