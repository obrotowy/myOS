#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <limits.h>
#include <stdlib.h>

int printf(const char* restrict format, ...) {
    int written = 0;
    size_t i = 0;
    va_list args;
    va_start(args, format);
    while (format[i] != '\0') {
        if (format[i] == '%') {
            ++i;
            switch (format[i]) {
                case '%':
                    putchar('%');
                    ++written;
                    break;

                case 'c':
                    putchar((char) va_arg(args, int));
                    ++written;
                    break;

                case 's':
                    written += puts((const char*) va_arg(args, const char*));
                    break;
                case 'd':
                case 'i': {
                    char digits[33];
                    itoa(va_arg(args, int), digits, 10);
                    written += puts(digits);
                    break;
                }
                case 'X': {
                    char digits[9];
                    itoa(va_arg(args, int), digits, 16);
                    written += printf("0x%s", digits);
                    break;
                }
                default:
                    putchar('%');
                    putchar(format[i]);
                    written += 2;
                    break;
            }
        }
        else {
            putchar(format[i]);
            ++written;
        }
        ++i;
    }
    va_end(args);
    return written;
}
