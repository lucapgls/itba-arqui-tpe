#include "sound.h"
#include "time.h"
#include <stdint.h>

void sound(uint8_t freq, uint64_t duration){
        uint64_t duration_s = duration * 1000;
       if(freq != 0)
          asm_start_sound(freq); // asm_start_sound(1193180 / freq);
        if(duration_s != 0)
            sleep(duration_s);
        if(!((freq == 0)^(duration_s == 0)))
        asm_end_sound();
}