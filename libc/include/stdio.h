#ifndef _STDIO
#define _STDIO

#define EOF (-1)

#ifdef _cplusplus
extern "C" {
#endif

int putchar(int ch);
int puts(const char* str);
int printf(const char* format, ...);
#ifdef _cplusplus
}
#endif

#endif