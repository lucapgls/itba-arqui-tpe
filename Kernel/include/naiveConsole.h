#ifndef NAIVE_CONSOLE_H
#define NAIVE_CONSOLE_H

#include <stdint.h>

void ncBackspace();
void ncPrint(const char * string);
void ncPrintColor(const char * string, const uint8_t fgColor, const uint8_t bgColor);
void ncPrintChar(char character);
void ncPrintCharColor(char character, uint8_t fgColor, uint8_t bgColor);
void ncNewline();
void ncPrintDec(uint64_t value);
void ncPrintHex(uint64_t value);
void ncPrintBin(uint64_t value);
void ncPrintBase(uint64_t value, uint32_t base);
void ncClear();
void setBgColor(uint8_t newBgColor);
void setFgColor(uint8_t newFgColor);
uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);
#endif