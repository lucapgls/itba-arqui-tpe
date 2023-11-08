#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdint.h>


void exceptions_dispatcher(uint32_t exception, uint64_t* stack);

void print_regs(uint64_t *stack);

void exc_set_restore_point(uint64_t ip, uint64_t sp, uint64_t bp);

#endif
