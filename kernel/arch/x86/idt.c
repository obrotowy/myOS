#include <idt.h>

IDT_Entry IDT[256];

void set_idtr() {
  IDTR idtr = {.size = 256 * 8 - 1, .offset = (uint64_t*)IDT};
  asm(
    ".intel_syntax noprefix;"
    "lidt [%0]"
    :
    : "r"(&idtr)
    : "eax"
  );
}