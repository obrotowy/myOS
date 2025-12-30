#include <ps2.h>
#include <kernel/tty.h>
#include <stdio.h>
const char kb_map[] = {
  0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 8,
  '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
  0 /*left ctrl here*/, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0 /*left shift*/, '\\',
  'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0 /*right shift*/, '*', 0 /*left alt*/, ' ', 0 /*caps lock*/,
  /* todo more*/
};

char kb_buf[255] = "";
uint8_t kb_buf_idx = 0;
void kb_handler(void) {
  uint8_t scancode = ps2_read_data();
  const char mapped = kb_map[scancode];
  if (kb_buf_idx < 255 && scancode <= 0x3B) {
    if (mapped == 8) {
      kb_buf[--kb_buf_idx] = 0;
      tty_setpos_rel(-1, 0);
      putchar(' ');
      tty_setpos_rel(-1, 0);
    }
    else {
      kb_buf[kb_buf_idx++] = kb_map[scancode];
      putchar(mapped);
    }
  }
}