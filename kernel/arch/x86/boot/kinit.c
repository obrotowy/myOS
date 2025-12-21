#include <kernel/tty.h>
#include <cpuid.h>
#include <paging.h>
#include <gdt.h>
#include <idt.h>

extern void tty32_puts(const char*);
extern void tty32_init();
extern void tty32_putc(const char);

void panic(const char* msg) {
  tty32_puts("[PANIC] ");
  tty32_puts(msg);
  for (;;);
}

void kinit() {
  tty32_init();
  
  if (check_cpuid_availability() && check_long_mode()) {
    tty32_puts("[+] Compatible x86-64 CPU detected.\n");
  }
  else {
    panic("Incompatible CPU.\n");
    return;
  }
  if (set_pae()) {
    tty32_puts("[+] PAE Enabled\n");
  }
  else {
    tty32_puts("[PANIC] Can't enable PAE.\n");
    return;
  }
  set_lme();
  set_gdt_entries();
  set_gdtr();
  set_idtr();
  if (init_page_tables()) {
    tty32_puts("[+] Paging enabled.\n");
  } else {
    panic("Failed to enable paging.");
  }
}