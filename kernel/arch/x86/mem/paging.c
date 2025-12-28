#include <stdint.h>
#include <stdbool.h>

uint64_t PML4[512];
uint64_t PDPT[512];
uint64_t PDT[512];

bool init_page_tables() {
  PML4[0] = (uint64_t) &PDPT | 0x3;

  PDPT[0] = (uint64_t) &PDT | 0x3;

  PDT[0] = 0x3 | (1 << 7);

  asm(
    ".intel_syntax noprefix;"
    "mov eax, %0;"
    "mov cr3, eax;"
    "mov eax, cr0;"
    "or eax, 0x80000000;"
    "mov cr0, eax;"
    :
    : "r"(PDPT)
    : "eax"
  );

  uint32_t cr0;
  asm("mov eax, cr0;" : "=r"(cr0));
  return (cr0 >> 31) & 0x1;
}

