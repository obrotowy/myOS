#pragma once
#include <stdint.h>

void tty_init();
void tty_puts(const char* );
void tty_putchar(char);
void tty_clear();
void tty_setpos_rel(int dx, int dy);
void tty_set_posx(unsigned x);
void tty_set_y(unsigned int y);
void tty_setcolor(unsigned int x, unsigned int y, uint16_t color);