#pragma once
#include <stdint.h>

typedef struct __attribute__((packed)) IDTR{
  uint16_t size;
  uint32_t* offset;
} IDTR;

typedef struct __attribute__((packed)) IDT_Entry {
  uint16_t isr_addr_low;
  uint16_t segment;
  uint8_t reserved;
  uint8_t attrs;
  uint16_t isr_addr_high;
} IDT_Entry;

void set_idtr();
void init_idt();