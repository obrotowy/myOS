#include <x86/idt.h>


IDT_Entry IDT[256] __attribute__((aligned(4096)));
extern void* isr_stub_table[];
extern void* isr_timer;
extern void* isr_kb;
void set_idtr() {
  IDTR idtr = {.size = 256 * 8 - 1, .offset = (uint32_t*)IDT};
  asm(
    ".intel_syntax noprefix;"
    "lidt [%0]"
    :
    : "r"(&idtr)
    : "eax"
  );
}

void init_idt() {
  for (int i = 0; i<32; ++i) {
    IDT[i] = (IDT_Entry) {
      .isr_addr_low = (uint32_t)isr_stub_table[i] & 0xFFFF,
      .segment = 0x08,
      .reserved = 0,
      .attrs = 0x8E,
      .isr_addr_high = (uint32_t)isr_stub_table[i] >> 16
    };
  }
  IDT[32] = (IDT_Entry) {
    .isr_addr_low = (uint32_t)&isr_timer & 0xFFFF,
    .segment = 0x08,
    .reserved = 0,
    .attrs = 0x8E,
    .isr_addr_high = (uint32_t)&isr_timer >> 16
  };
  IDT[33] = (IDT_Entry) {
    .isr_addr_low = (uint32_t)&isr_kb & 0xFFFF,
    .segment = 0x08,
    .reserved = 0,
    .attrs = 0x8E,
    .isr_addr_high = (uint32_t)&isr_kb >> 16
  };
}