#include <boot/multiboot2.h>
#include <kernel/tty.h>
#include <kernel/panic.h>
#include <stdio.h>
#include <x86/paging.h>
#include <x86/gdt.h>
#include <x86/idt.h>
#include <x86/port.h>
#include <x86/pic.h>
#include <x86/mouse.h>
#include <x86/ps2.h>
#include <stddef.h>
#include <x86/kb.h>

struct multiboot_header_tag* multiboot_tag = NULL;

void kinit(uint32_t magic, struct multiboot_header_tag* struct_addr) {
  if (magic != MULTIBOOT2_BOOTLOADER_MAGIC)
    printf("[!] OS was loaded using unsupported bootloader. Use carefully.\n");
  else
    multiboot_tag = struct_addr;
  tty_init();
  PIC_remap(0x20, 0x28);
  outb(0x21, 0xFF); // Enable PIT, Keyboard and Cascade
  outb(0xA1, 0xEF);
  set_gdt_entries();
  set_gdtr();
  init_idt();
  set_idtr();
  init_page_tables();
  ps2_init();
  kb_init();
  mouse_init();
}