include Makefile.inc

KERNEL=kernel.bin
# KERNEL_ELF=$(KERNEL:.bin=.elf)

SOURCES=$(wildcard *.c)
SOURCES_DRIVERS=$(wildcard drivers/*.c)
SOURCES_IDT=$(wildcard idt/*.c)
SOURCES_ASM=$(wildcard asm/*.asm)
SOURCES_UTILS=$(wildcard utils/*.c)

OBJECTS=$(SOURCES:.c=.o)
OBJECTS_DRIVERS=$(SOURCES_DRIVERS:.c=.o)
OBJECTS_IDT=$(SOURCES_IDT:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)
OBJECTS_UTILS=$(SOURCES_UTILS:.c=.o)

ALL_OBJECTS= $(OBJECTS) $(OBJECTS_DRIVERS) $(OBJECTS_IDT) $(OBJECTS_ASM) $(OBJECTS_UTILS)


LOADERSRC=loader.asm
LOADEROBJ=$(LOADERSRC:.asm=.o)
STATICLIBS=

all: $(KERNEL)

$(KERNEL): $(LOADEROBJ) $(STATICLIBS) $(ALL_OBJECTS)
	$(LD) $(LDFLAGS) -T kernel.ld -o $(KERNEL) $(LOADEROBJ) $(STATICLIBS) $(ALL_OBJECTS)

%.o: %.c
	$(GCC) $(GCCFLAGS) -I./include -c $< -o $@

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

$(LOADEROBJ):
	$(ASM) $(ASMFLAGS) $(LOADERSRC) -o $(LOADEROBJ)

clean:
	rm -rf *.bin *.elf *.o drivers/*.o idt/*.o libasm/*.o libc/*.o

.PHONY: all clean