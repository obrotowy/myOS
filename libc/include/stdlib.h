#ifndef _STDLIB
#define _STDLIB
#include <stdint.h>
char* itoa(int value, char* str, const int base);
char* uitoa(uint32_t value, char* str, const int base);
#endif