#include <idtLoader.h>
#include <io.h>
#include <keyboard.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <sound.h>
#include <stdint.h>
#include <string.h>
#include <syscalls.h>
#include <time.h>
#include <userland.h>
#include <video.h>

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

void clearBSS(void *bssAddress, uint64_t bssSize) {
    memset(bssAddress, 0, bssSize);
}

void *getStackBase() {
    return (void *)((uint64_t)&endOfKernel + PageSize * 8 // The size of the stack itself, 32KiB
                    - sizeof(uint64_t) // Begin at the top of the stack
    );
}

void *initializeKernelBinary() {

    void *moduleAddresses[] = {
        userlandCodeModuleAddress,
        sampleDataModuleAddress};

    loadModules(&endOfKernelBinary, moduleAddresses);

    clearBSS(&bss, &endOfKernel - &bss);

    return getStackBase();
}

int main() {

    idt_loader();

    printf_color("Welcome to the AmongOS kernel!\n", 0x00FF00, 0x00);

    ((EntryPoint)userlandCodeModuleAddress)();

    while (1)
        ;

    return 0;
}
