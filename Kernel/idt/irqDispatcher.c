#include <stdint.h>
#include <time.h>

#define TIMER 0

void irq_dispatcher(uint64_t irq){
    switch(irq){
        case TIMER: {
            timer_handler();
                break;
        } 
        return; 
}
}