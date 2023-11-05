#include "sound.h"
#include "time.h"
#include "lib.h"
#include <stdint.h>

void sound(uint8_t freq, uint64_t duration){
        uint64_t duration_s = duration * 1000;
       if(freq != 0)
          asm_start_sound(freq); // asm_start_sound(1193180 / freq);
        if(duration_s != 0)
            sleep(duration_s);
        if(!((freq == 0) && (duration_s == 0)))
        asm_end_sound();
}

//Play sound using built in speaker
 static void play_sound(uint32_t nFrequence) {
 	uint32_t Div;
 	uint8_t tmp;
 
        //Set the PIT to the desired frequency
 	Div = 1193180 / nFrequence;
 	outb(0x43, 0xb6);
 	outb(0x42, (uint8_t) (Div) );
 	outb(0x42, (uint8_t) (Div >> 8));
 
        //And play the sound using the PC speaker
 	tmp = inb(0x61);
  	if (tmp != (tmp | 3)) {
 		outb(0x61, tmp | 3);
 	}
 }
 
 //make it shutup
 static void nosound() {
 	uint8_t tmp = inb(0x61) & 0xFC;
 
 	outb(0x61, tmp);
 }
 
 //Make a beep
 void beep() {
 	 play_sound(1000);
 	 sleep(100);
 	 nosound();
          //set_PIT_2(old_frequency);
 }