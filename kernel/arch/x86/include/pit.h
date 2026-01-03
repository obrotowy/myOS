#pragma once
#include <port.h>

static inline void pit2_set_freq(uint32_t freq) {
  uint16_t div = 1193182 / freq;
  outb(0x41, 0xb6);
  outb(0x42, (uint8_t) (div));
  outb(0x42, (uint8_t) (div >> 8));
}