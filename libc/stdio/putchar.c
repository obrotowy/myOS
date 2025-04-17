#include <stdio.h>
#if defined(__is_libk)
#include <kernel/tty.h>
#endif


int putchar(int ch) {
    #if defined(__is_libk)
    tty_putchar(ch);
    #endif

    return ch;
}