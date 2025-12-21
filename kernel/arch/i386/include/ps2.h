#pragma once
#include <stdint.h>
#include <port.h>
#include <stdio.h>

#define PS2_STATUS_REGISTER 0x60
#define PS2_COMMAND_REGISTER 0x64
#define PS2_DATA_PORT 0x60


static inline uint8_t ps2_read_status() {
  return inb(PS2_STATUS_REGISTER);
}

static inline uint8_t ps2_read_data() {
  for (int i = 0; i<1024; ++i) {
    if (ps2_read_status() & 1)
      return inb(PS2_DATA_PORT);
  }
  printf("[ps2] reading data timed out.\n");
  return 0;
}

static inline void ps2_write_cmd(uint8_t cmd) {
  for (int i = 0; i<1024; ++i) {
    if (!(ps2_read_status() & 0b10)) {
      outb(PS2_COMMAND_REGISTER, cmd);
      return;
    }
  }
  printf("[ps2] sending %X command failed due to time out.\n", cmd);
}

static inline void ps2_write_data(uint8_t data) {
  for (int i = 0; i<1024; ++i) {
    if (!(ps2_read_status() & 0b10)) {
      outb(PS2_DATA_PORT, data);
      return;
    }
  }
  printf("[ps2] sending %X data failed due to time out.\n", data);
}