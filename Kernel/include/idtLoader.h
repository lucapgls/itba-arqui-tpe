/******************************************************************************
 *
 * @file    idtLoader.h
 *
 * @brief   IDT Loader. Manages interruptions
 *
 * @author  Luca Pugliese                           <lpugliese@itba.edu.ar>
 * @author  Felipes Venturino                        <fventurino@itba.edu.ar>
 * @author  Uriel Sosa Vazquez                      <usosavazquez@itba.edu.ar>
 *
 ******************************************************************************/
#include <stdint.h>



extern void asm_cli();
extern void asm_sti();

extern void pic_master_mask(uint8_t mask);
extern void pic_slave_mask(uint8_t mask);

/* 
 * @name asm_irq00_handler
 * @brief Handles the keyboard interruption.
 * 
 */
extern void asm_irq00_handler();
/*
 * @name asm_irq01_handler
 * @brief Handles the timer interruption.
 * 
 */
extern void asm_irq01_handler();

/*
 * @name asm_exception00_handler
 * @brief Handles the division by zero exception.
 * 
 */
extern void asm_exception00_handler();
/*
 * @name asm_exception06_handler
 * @brief Handles the invalid opcode exception.
 * 
 */
extern void asm_exception06_handler();

/*
 * @name asm_syscall80_handler
 * @brief Handles the system call interruption.
 * 
 */
extern void asm_syscall80_handler();

/*
 * @name idt_loader
 * @brief Loads the IDT.
 */
void idt_loader();
