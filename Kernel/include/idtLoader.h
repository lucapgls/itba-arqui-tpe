#include <stdint.h>

extern void asm_cli();
extern void asm_sti();

extern void pic_master_mask(uint8_t mask);
extern void pic_slave_mask(uint8_t mask);

extern void asm_irq00_handler();
extern void asm_irq01_handler();
extern void asm_syscall80_handler();

void idt_loader();
