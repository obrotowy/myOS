#pragma once
#include <stdint.h>

static inline void outb(uint16_t port, uint8_t val) {
  asm volatile(
    "out dx, al"
    :
    : "a"(val), "d"(port)
    : "memory"
  );
}

static inline void outw(uint16_t port, uint16_t val) {
  asm volatile(
    "out dx, ax"
    :
    : "a"(val), "d"(port)
    : "memory"
  );
}

static inline void outd(uint16_t port, uint32_t val) {
  asm volatile(
    "out dx, eax"
    :
    : "a"(val), "d"(port)
    : "memory"
  );
}

static inline uint8_t inb(uint16_t port) {
  uint8_t ret;
  asm volatile(
    "in al, dx"
    : "=a"(ret)
    : "d"(port)
    : "memory"
  );
  return ret;
}

static inline uint16_t inw(uint16_t port) {
  uint16_t ret;
  asm volatile(
    "in ax, dx"
    : "=a"(ret)
    : "d"(port)
    : "memory"
  );
  return ret;
}

static inline uint16_t ind(uint16_t port) {
  uint32_t ret;
  asm volatile(
    "in eax, dx"
    : "=a"(ret)
    : "d"(port)
    : "memory"
  );
  return ret;
}

static inline void io_wait() {
  outb(0x80, 0);
}