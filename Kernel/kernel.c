#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <keyboard.h>
#include <time.h>
#include <idtLoader.h>

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();


void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{
	char buffer[10];

	ncPrint("CPU Vendor:");
	ncPrint(cpuVendor(buffer));
	ncNewline();

	ncPrint("[Loading modules]");
	ncNewline();
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	ncPrint("[Done]");
	ncNewline();
	ncNewline();

	ncPrint("[Initializing kernel's binary]");
	ncNewline();

	clearBSS(&bss, &endOfKernel - &bss);

	ncPrint("  text: 0x");
	ncPrintHex((uint64_t)&text);
	ncNewline();
	ncPrint("  rodata: 0x");
	ncPrintHex((uint64_t)&rodata);
	ncNewline();
	ncPrint("  data: 0x");
	ncPrintHex((uint64_t)&data);
	ncNewline();
	ncPrint("  bss: 0x");
	ncPrintHex((uint64_t)&bss);
	ncNewline();

	ncPrint("[Done]");
	ncNewline();

	for (int i = 0; i < 250; i++) {
		ncPrintColor("a", i, 250-i);
	}
    ncNewline();

	getTime();
	// ncPrintDec(getSeconds());
    ncNewline();

    ncNewline();

	return getStackBase();
}

int main()
{	

	idt_loader();
	ncPrintDec(seconds_elapsed());
	// ncClear();

	ncNewline();
	ncNewline();
	ncPrint("[Kernel Main]");
	ncNewline();
	ncNewline();

	char buffer[1] = {0};
	int i = 0;

	// temp (cualquier cosa para probar el input.)
	while(1) {
		if (getKey() != 0) {
			buffer[i++] = getKey();
		}
		if (i == 1) {
			i = 0;
			if (buffer[0] == '\b') {
				ncBackspace();
				break;
			} else {
			ncPrint(buffer);
			// putKey(buffer[0]);
			}
		}

	}

	// ncNewline();
	// ncPrint("  Sample code module at 0x");
	// ncPrintHex((uint64_t)sampleCodeModuleAddress);
	// ncNewline();
	// ncPrint("  Calling the sample code module returned: ");
	// ncPrintHex(((EntryPoint)sampleCodeModuleAddress)());
	// ncNewline();
	// ncNewline();

	// ncPrint("  Sample data module at 0x");
	// ncPrintHex((uint64_t)sampleDataModuleAddress);
	// ncNewline();
	// ncPrint("  Sample data module contents: ");
	// ncPrint((char*)sampleDataModuleAddress);
	// ncNewline();
	ncNewline();
	// putKey();



	ncPrint("[Finished]");
	return 0;
}
