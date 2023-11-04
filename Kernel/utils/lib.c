#include <stdint.h>
#include <naiveConsole.h>

#define TIMEZONE -3 // argentina


void * memset(void * destination, int32_t c, uint64_t length)
{
	uint8_t chr = (uint8_t)c;
	char * dst = (char*)destination;

	while(length--)
		dst[length] = chr;

	return destination;
}

void * memcpy(void * destination, const void * source, uint64_t length)
{
	/*
	* memcpy does not support overlapping buffers, so always do it
	* forwards. (Don't change this without adjusting memmove.)
	*
	* For speedy copying, optimize the common case where both pointers
	* and the length are word-aligned, and copy word-at-a-time instead
	* of byte-at-a-time. Otherwise, copy by bytes.
	*
	* The alignment logic below should be portable. We rely on
	* the compiler to be reasonably intelligent about optimizing
	* the divides and modulos out. Fortunately, it is.
	*/
	uint64_t i;

	if ((uint64_t)destination % sizeof(uint32_t) == 0 &&
		(uint64_t)source % sizeof(uint32_t) == 0 &&
		length % sizeof(uint32_t) == 0)
	{
		uint32_t *d = (uint32_t *) destination;
		const uint32_t *s = (const uint32_t *)source;

		for (i = 0; i < length / sizeof(uint32_t); i++)
			d[i] = s[i];
	}
	else
	{
		uint8_t * d = (uint8_t*)destination;
		const uint8_t * s = (const uint8_t*)source;

		for (i = 0; i < length; i++)
			d[i] = s[i];
	}

	return destination;
}

static uint32_t format(uint8_t num)
{
	int dec = (num & 240) >> 4;
	int units = num & 15;
	return dec * 10 + units;
}

uint32_t getSeconds() {
	return format(rtcTime(0x00));
}
uint32_t getMinutes() {
	return format(rtcTime(0x02));
}
uint32_t getHours() {
	return format(rtcTime(0x04)) + TIMEZONE;
}

void getTime() {
	ncPrintDec(getHours());
	ncPrint(":");
	ncPrintDec(getMinutes());
	ncPrint(":");
	ncPrintDec(getSeconds());
}

void itoa(char* str, int num, int width) {
    for (int i = width - 1; i >= 0; i--) {
        str[i] = num % 10 + '0';
        num /= 10;
    }
    str[width] = '\0';
}

uint64_t get_random_number(int seed){

	unsigned int m = 2147483648; // Modulus
	unsigned int a = 1664525;    // Multiplier
	unsigned int c = 1013904223; // Increment
	return ((a * seed * (ticks_elapsed() % a) + c) % m) % UINT32_MAX;
	// //return (seed * (rtcTime(0x00) + rtcTime(0x02) / rtcTime(0x00) % seed) / ticks_elapsed()) % UINT32_MAX;
}