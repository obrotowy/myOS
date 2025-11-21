#include <kernel/tty.h>
#include <kernel/panic.h>
#include <cpuid.h>
#include <stdio.h>

void kinit() {
  tty_init();
  
  if (check_cpuid_availability() && check_long_mode()) {
    puts("[+] Compatible x86-64 CPU detected.\n");
  }
  else {
    panic("Incompatible CPU.\n");
    return;
  }
  if (set_pae()) {
    puts("[+] PAE Enabled\n");
  }
  else {
    puts("[PANIC] Can't enable PAE.\n");
    return;
  }
  set_lme();
}