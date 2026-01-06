#include <stdio.h>
#include <x86/port.h>
#include <x86/ps2.h>
void kmain() {
  while (ps2_read_status() & PS2_OUTPUT_BUFFER_STATUS_BIT)
    ps2_read_data();
  outb(0x21, 0xF8); // Enable PIT, Keyboard and Cascade
  puts("OS fully loaded\n");
  puts("> ");
}