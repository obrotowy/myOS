#include <kernel/tty.h>
#include <kernel/panic.h>
#include <cpuid.h>
#include <stdio.h>
#include <paging.h>
#include <gdt.h>
#include <idt.h>
#include <port.h>
#include <pic.h>

void kinit() {
  tty_init();
  // Disable IRQs since we need to program PIC first to IRQ not overlap with CPU Exceptions
  
  PIC_remap(0x20, 0x28);
  outb(0x21, 0xFE); // Mask everytihg except Timer IRQ
  outb(0xA1, 0xFF);
  if (check_cpuid_availability()) {
    puts("[+] CPUID Available.\n");
  }
  else {
    panic("Incompatible CPU.\n");
    return;
  }
  set_gdt_entries();
  set_gdtr();
  init_idt();
  set_idtr();
  init_page_tables();
}