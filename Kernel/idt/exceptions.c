#include <exceptions.h>
#include <io.h>

#define ERROR_FGCOLOR 0xFF0000
#define ERROR_BGCOLOR 0x000000
#define ZERO_DIVISION 0
#define INVALID_OPCODE  6
#define BUFF_SIZE 30

static char buff[BUFF_SIZE];

static char * regs[] = {
        "R15 = 0x", "R14 = 0x", "R13 = 0x", "R12 = 0x", "R11 = 0x", "R10 = 0x", "R9 = 0x", "R8 = 0x", "RSI = 0x",
         "RDI = 0x", "RBP = 0x", "RDX = 0x", "RCX = 0x", "RBX = 0x", "RAX = 0x", "IP = 0x", "RSP = 0x",  
};

static uint32_t registers_len = sizeof(regs)/sizeof(regs[0]);


void exception_dispatcher(uint32_t exception, uint64_t* stack){
    switch(exception){
        case ZERO_DIVISION:
                printf_color("Zero Division Error Exception\n",ERROR_FGCOLOR, ERROR_BGCOLOR);
        break;
        case INVALID_OPCODE:
                printf_color("Invadid Opcode Exception\n", ERROR_FGCOLOR,ERROR_BGCOLOR);
        break;
    }
    printregs(stack);
}


void printregs(uint64_t * stack){
    /*
    if(stack == 0){
        return;
    }
    */
    for(int i = 0; i < registers_len - 1; i++){
       //uint32_t len = 
       printf("%s", regs[i]);
        
    }
}