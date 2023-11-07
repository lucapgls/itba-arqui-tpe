#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdint.h>


void exceptions_dispatcher(uint32_t exception, uint64_t* stack);

void print_regs(uint64_t *stack);

#endif
