#include <stdint.h>
#include <stdbool.h>

uint32_t PD[1024] __attribute__((aligned(4096)));;
uint32_t PT[1024] __attribute__((aligned(4096)));;


bool init_page_tables() {
  // Identity map 2MB
  for (int i = 0; i<=0x200; ++i) {
    PT[i] = (i << 12) | 3;
  }
  PD[0] = ((uint32_t)PT & 0xFFFFF000) | 3;
  for (int i = 1; i<1024; ++i) {
    PD[i] = 0;
  }

  
  asm volatile(
    ".intel_syntax noprefix;"
    "mov eax, %0;"
    "mov cr3, eax;"
    "mov eax, cr0;"
    "or eax, 0x80000000;"
    "mov cr0, eax;"
    :
    : "r"(PD)
    : "eax", "memory"
  );
  

  uint32_t cr0;
  asm("mov eax, cr0;" : "=r"(cr0));
  return (cr0 >> 31) & 0x1;
}

