#include <stdint.h>
#include <gdt.h>
uint64_t GDT[3];

void set_gdt_entries() {
  GDT[0] = 0;   // Null Entry
  // Kernel Mode Code Segment
  GDT[1] = (0xAull << 52) | (0x9Aull << 40) | (0xFull << 48) | 0xFFFF;
  // Kernel Mode Data Segment
  GDT[2] = (0xCull << 52) | (0x92ull << 40) | (0xFull << 48) | 0xFFFF; 
}

void set_gdtr() {
  GDTR gdtr = {.base = GDT, .limit=3*8-1};
  asm(
    ".intel_syntax noprefix;"
    "lgdt [%0]"
    :
    : "r"(&gdtr)
    : "eax"
  );
}
