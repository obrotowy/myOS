#pragma once
#include <stdint.h>
#include <x86/port.h>
#include <stdio.h>

#define PS2_STATUS_PORT 0x64
#define PS2_COMMAND_PORT 0x64
#define PS2_DATA_PORT 0x60
#define PS2_OUTPUT_BUFFER_STATUS_BIT 1
#define PS2_INPUT_BUFFER_STATUS_BIT 2

#define PS2_ENABLE_SCANNING 0xF4
#define PS2_DISABLE_SCANNING 0xF5
#define PS2_DEVICE_ACK 0xFA
#define PS2_DEVICE_IDENTIFY 0xF2


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

static inline void ps2_send_data_second_device(uint8_t data) {
  ps2_send_command(0xD4);
  io_wait();
  ps2_send_data(data);
}

static inline uint8_t ps2_get_config() {
  ps2_send_command(0x20);
  return ps2_read_data();
}

static inline void ps2_send_config(uint8_t cfg) {
  ps2_send_command(0x60);
  ps2_send_data(cfg);
}

static inline void ps2_wait_for_ack() {
  do {} while(ps2_read_data() != PS2_DEVICE_ACK);
}

static inline void ps2_flush_buffer() {
  while (ps2_read_status() & PS2_OUTPUT_BUFFER_STATUS_BIT)
    ps2_read_data();
}

void ps2_init();