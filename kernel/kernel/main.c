#include <kernel/tty.h>
#include <cpuid.h>
#include <stdio.h>

void kmain() {
    tty_init();
    if (check_cpuid_availability() && check_long_mode()) {
      puts("[+] Compatible x86-64 CPU detected.\n");
    }
    else {
      puts("[PANIC] Incompatible CPU.\n");
      return;
    }
}