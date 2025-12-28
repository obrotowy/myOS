#include "multiboot.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <kernel/tty.h>

extern void set_gdt_entries();
extern void set_gdtr();

void lmain(const void* multiboot_struct) {
  tty_init();
  set_gdt_entries();
  set_gdtr();

  const multiboot_info_t* mb_info = multiboot_struct;
	multiboot_uint32_t mb_flags = mb_info->flags;
  void* kentry = NULL;
  if (mb_flags & MULTIBOOT_INFO_MODS) {
    multiboot_uint32_t mods_count = mb_info->mods_count;
		multiboot_uint32_t mods_addr = mb_info->mods_addr;
    printf("[multiboot] found %d modules.\n", (int32_t) mods_count);
    for (uint32_t mod = 0; mod < mods_count; mod++) {
      multiboot_module_t* module = (multiboot_module_t*)(mods_addr + (mod * sizeof(multiboot_module_t)));
    }
  }
}