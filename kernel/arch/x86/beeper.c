#include <beeper.h>
#include <pit.h>
#include <stdio.h>

extern uint64_t ticks;

static void play_sound(uint32_t freq) {
  pit2_set_freq(freq);
  uint8_t tmp = inb(0x61);
  if (tmp != (tmp | 3)) {
    outb(0x61, tmp | 3);
  }
}

static void no_sound() {
  uint8_t tmp = inb(0x61) & 0xFC;
  outb(0x61, tmp);
  pit2_set_freq(65536);
}

void beep() {
  play_sound(1000);
  no_sound();
}