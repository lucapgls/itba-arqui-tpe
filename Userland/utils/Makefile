include ../Makefile.inc

# MODULE=0000-sampleCodeModule.bin
MODULE=0000-userlandCodeModule.bin
SOURCES=$(wildcard *.c)
SOURCES_EXEC=$(wildcard exec/*.c)
SOURCES_LIBC=$(wildcard libc/*.c)
SOURCES_ASM=$(wildcard libasm/*.asm)

OBJECTS=$(SOURCES:.c=.o)
OBJECTS_EXEC=$(SOURCES_EXEC:.c=.o)
OBJECTS_LIBC=$(SOURCES_LIBC:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)

ALL_OBJECTS= $(OBJECTS) $(OBJECTS_ASM) $(OBJECTS_EXEC) $(OBJECTS_LIBC)

all: $(MODULE)

$(MODULE): $(ALL_OBJECTS)
	$(LD) $(LDFLAGS) -T userlandCodeModule.ld $(ALL_OBJECTS) -o ../$(MODULE)
	$(LD) $(LDFLAGS) -T userlandCodeModule.ld --oformat=elf64-x86-64 -o ../0000-userlandCodeModule.elf $^

%.o: %.c
	$(GCC) $(GCCFLAGS) -I./include -c $< -o $@

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	@rm -rf *.o
	@rm -rf exec/*.o
	@rm -rf libasm/*.o

.PHONY: all clean print