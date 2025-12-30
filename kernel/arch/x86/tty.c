#include <kernel/tty.h>
#include <vga.h>
#include <stdint.h>
#include <stddef.h>

static uint16_t* vga_buffer;
static uint8_t tty_x;
static uint8_t tty_y;
static uint8_t tty_color;

void tty_init() {
  vga_buffer = (uint16_t*) VGA_BUFFER_ADDR;
  tty_x = 0;
  tty_y = 0;
  tty_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  tty_clear();
}

void tty_putchar(char c) {
  if (c == '\n') {
    tty_x = 0;
    tty_y++;
  } else if (c == '\r') {
    tty_x = 0;
  } else {
    const size_t index = tty_y * VGA_WIDTH + tty_x;
    vga_buffer[index] = vga_entry(c, tty_color);
    tty_x++;
  }

  if (tty_x >= VGA_WIDTH) {
    tty_x = 0;
    tty_y++;
  }
  if (tty_y >= VGA_HEIGHT) {
    tty_y = 0;
  }
}

void tty_puts(const char* s) {
  while (*s) {
    tty_putchar(*s++);
  }
}

void tty_setx(unsigned int x) {
  tty_x = x;
}

void tty_sety(unsigned int y) {
  tty_y = y;
}

void tty_clear() {
  for (size_t i = 0; i<VGA_WIDTH * VGA_HEIGHT; ++i) {
    vga_buffer[i] = vga_entry(0, tty_color);
  }
  tty_setx(0);
  tty_sety(0);
}

void tty_setpos_rel(int dx, int dy) {
  tty_x += dx;
  tty_y += dy;
}
