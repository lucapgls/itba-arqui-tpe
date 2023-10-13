include Makefile.inc

KERNEL=kernel.bin
# KERNEL_ELF=$(KERNEL:.bin=.elf)

SOURCES=$(wildcard *.c)
SOURCES_DRIVERS=$(wildcard drivers/*.c)
SOURCES_IDT=$(wildcard idt/*.c)
SOURCES_ASM=$(wildcard asm/*.asm)

OBJECTS=$(SOURCES:.c=.o)
OBJECTS_DRIVERS=$(SOURCES_DRIVERS:.c=.o)
OBJECTS_IDT=$(SOURCES_IDT:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)

LOADERSRC=loader.asm
LOADEROBJ=$(LOADERSRC:.asm=.o)
STATICLIBS=

all: $(KERNEL)

$(KERNEL): $(LOADEROBJ) $(STATICLIBS) $(OBJECTS) $(OBJECTS_DRIVERS) $(OBJECTS_IDT) $(OBJECTS_ASM)
	$(LD) $(LDFLAGS) -T kernel.ld -o $(KERNEL) $(LOADEROBJ) $(STATICLIBS) $(OBJECTS) $(OBJECTS_DRIVERS) $(OBJECTS_IDT) $(OBJECTS_ASM)

%.o: %.c
	$(GCC) $(GCCFLAGS) -I./include -c $< -o $@

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

$(LOADEROBJ):
	$(ASM) $(ASMFLAGS) $(LOADERSRC) -o $(LOADEROBJ)

clean:
	rm -rf *.bin *.elf *.o drivers/*.o idt/*.o libasm/*.o libc/*.o

.PHONY: all clean