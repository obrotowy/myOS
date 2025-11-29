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
  for (size_t y = 0; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t index = y * VGA_WIDTH + x;
      vga_buffer[index] = vga_entry(' ', tty_color);
    }
  }
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