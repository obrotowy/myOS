#include <x86/ps2.h>
#include <stdbool.h>
#include <stdint.h>
#include <x86/vga.h>
#include <kernel/tty.h>


static uint16_t* vga_buf = (uint16_t*) 0xB8000;
static uint8_t x = VGA_WIDTH / 2;
static uint8_t y = VGA_HEIGHT / 2;

void mouse_init() {
  ps2_send_data_second_device(PS2_DISABLE_SCANNING);
  ps2_wait_for_ack();

  ps2_send_data_second_device(0xF6);
  ps2_wait_for_ack();
  ps2_send_data_second_device(PS2_ENABLE_SCANNING);
  ps2_wait_for_ack();
}

void mouse_handler() {
  uint8_t flags;
  do {
    flags = ps2_read_data();
  } while (!(flags & 0x08));
  int16_t dx = ps2_read_data();
  int16_t dy = ps2_read_data();

  if (flags & 0b11000000) // Check for X or Y overflow
    return;

  if (flags & 1)
    puts("[mouse] Left button clicked.\n");
  if (flags & 2)
    puts("[mouse] Right button clicked.\n");
  if (!(flags & 0x20))   // Negative Y
    dy |= 0xFF00;
  if (flags & 0x10)   // Negative X
    dx |= 0xFF00;
  tty_setcolor(x, y, vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
  x += (dx % 2);
  y += (dy % 2);
  tty_setcolor(x, y, vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_LIGHT_BLUE));
  ps2_flush_buffer();
}