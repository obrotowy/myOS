#include <stdint.h>
#include <stdio.h>

typedef uint64_t GDTR;
typedef uint64_t GDT_Entry;

GDT_Entry entries[3];

void set_gdt_entries() {
  entries[0] = 0; // Null Descriptor
  entries[1] = (0xFull << 48) | (0x9Aull << 40) | (0xCull << 52) | 0xFFFFul;  // Code segment
  entries[2] = (0xFull << 48) | (0x92ull << 40) | (0xCull << 52) | 0xFFFFul;  // Data segment
}

void set_gdtr() {
  GDTR gdtr = ((uint64_t) &entries << 16) | (3*sizeof(GDT_Entry)-1);
  printf("GDTR Value: %X\n", gdtr);
    asm(
    ".intel_syntax noprefix;"
    "lgdt [%0]"
    :
    : "r"(&gdtr)
    : "eax"
  );
}