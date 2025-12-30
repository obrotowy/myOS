#ifndef STRING_H
#define STRING_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

size_t strlen(const char*);
void* memmove(void* dest, const void* src, size_t size);
void* memcpy(void* dest, const void* src, size_t size);
void* memset(void* dest, int ch, size_t size);
int memcmp(const void* lhs, const void* rhs, size_t count);
int strcmp(const char* lhs, const char* rhs);
#ifdef __cplusplus
}
#endif

#endif