#pragma once
#include <stdint.h>
#include <port.h>
#include <stdio.h>


static inline uint8_t ps2_read_status() {
  return inb(0x64);
}

static inline uint8_t ps2_read_data() {
  while (1) {
    if (ps2_read_status() & 1)
      return inb(0x60);
  }
}
