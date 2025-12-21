#pragma once
#include <stdint.h>

typedef struct __attribute__((packed)) GDTR{
  uint16_t limit;
  uint64_t* base;
} GDTR;

void set_gdt_entries();
void set_gdtr();