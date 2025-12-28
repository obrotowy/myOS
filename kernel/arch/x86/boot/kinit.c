#include <kernel/tty.h>
#include <kernel/panic.h>
#include <cpuid.h>
#include <stdio.h>
#include <paging.h>
#include <gdt.h>
#include <idt.h>

void kinit() {
  tty_init();
  
  if (check_cpuid_availability()) {
    puts("[+] CPUID Available.\n");
  }
  else {
    panic("Incompatible CPU.\n");
    return;
  }
  set_gdt_entries();
  set_gdtr();
  //set_idtr();
  //if (init_page_tables()) {
  //  puts("[+] Paging enabled.\n");
  //} else {
  //  panic("Failed to enable paging.");
  //}
}