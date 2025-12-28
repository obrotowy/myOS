#include <kernel/tty.h>
#include <kernel/panic.h>
#include <cpuid.h>
#include <stdio.h>
#include <paging.h>
#include <gdt.h>
#include <idt.h>
#include <multiboot.h>

void kinit(const void* multiboot_struct) {
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
  set_gdt_entries();
  set_gdtr();
  set_idtr();
  if (init_page_tables()) {
    puts("[+] Paging enabled.\n");
  } else {
    panic("Failed to enable paging.");
  }
  const multiboot_info_t* mb_info = multiboot_struct;
  multiboot_uint32_t mb_flags = mb_info->flags;
  void* kentry = NULL;

  if (mb_flags & MULTIBOOT_INFO_MODS) {
    multiboot_uint32_t mods_count = mb_info->mods_count;
    multiboot_uint32_t mods_addr = mb_info->mods_addr;
    for (uint32_t mod = 0; mod < mods_count; ++mod) {
      multiboot_module_t* module = (multiboot_module_t*) (mods_addr + (mod * sizeof(multiboot_module_t)));
    }
  }
}