#pragma once
#include <stdint.h>

typedef struct __attribute__((packed)) IDTR{
  uint16_t size;
  uint64_t* offset;
} IDTR;

typedef struct __attribute__((packed)) IDT_Entry {
  uint16_t offset_low;
  uint16_t segment_selector;
  uint16_t flags;
  uint16_t offset_middle;
  uint32_t offset_high;
  uint32_t reserved;
} IDT_Entry;

void set_idtr();