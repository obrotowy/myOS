#pragma once
#include <stdint.h>
#include <port.h>
#include <stdio.h>

#define PS2_STATUS_PORT 0x64
#define PS2_COMMAND_PORT 0x64
#define PS2_DATA_PORT 0x60
#define PS2_OUTPUT_BUFFER_STATUS_BIT 1
#define PS2_INPUT_BUFFER_STATUS_BIT 2

static inline uint8_t ps2_read_status() {
  return inb(PS2_STATUS_PORT);
}

static inline uint8_t ps2_read_data() {
  while (1) {
    if (ps2_read_status() & PS2_OUTPUT_BUFFER_STATUS_BIT)
      return inb(PS2_DATA_PORT);
  }
}

static inline void ps2_send_data(uint8_t data) {
  while (1) {
    if (!(ps2_read_status() & PS2_INPUT_BUFFER_STATUS_BIT)) {
      outb(PS2_DATA_PORT, data);
      return;
    }
  }
}

static inline void ps2_send_command(uint8_t cmd) {
  while (1) {
    if (!(ps2_read_status() & PS2_INPUT_BUFFER_STATUS_BIT)) {
      outb(PS2_COMMAND_PORT, cmd);
      return;
    }
  }
}