#include <stdint.h>
#include <naiveConsole.h>

#define TIMEZONE -3 // argentina

static uint32_t format(uint8_t num)
{
	int dec = (num & 240) >> 4;
	int units = num & 15;
	return dec * 10 + units;
}

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

/* Hardcodded, cambiar a un enum? */

uint8_t getSeconds() {
	return format(rtcTime(0x00));
}
uint8_t getMinutes() {
	return format(rtcTime(0x02));
}
uint8_t getHours() {
	return format(rtcTime(0x04)) + TIMEZONE;
}

void getTime() {
	ncPrintDec(getHours());
	ncPrint(":");
	ncPrintDec(getMinutes());
	ncPrint(":");
	ncPrintDec(getSeconds());
}

uint64_t get_random_number(){
	return ticks_elapsed() * getSeconds() * ('u'+ 'w' + 'u');  
}