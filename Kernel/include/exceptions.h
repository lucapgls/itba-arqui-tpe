/******************************************************************************
 *
 * @file    exceptions.h
 *
 * @brief   Exceptions handler.
 *
 * @author  Luca Pugliese                           <lpugliese@itba.edu.ar>
 * @author  Felipes Venturino                        <fventurino@itba.edu.ar>
 * @author  Uriel Sosa Vazquez                      <usosavazquez@itba.edu.ar>
 *
 ******************************************************************************/
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdint.h>


/*
 * @name exceptions_dispatcher
 * @brief Handles the exceptions.
 */
void exceptions_dispatcher(uint32_t exception, uint64_t* stack);

/* 
 * @name print_regs
 * @brief Prints the registers.
 */
void print_regs(uint64_t *stack);

#endif
