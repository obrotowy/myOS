#include <boot/multiboot2.h>
#include <kernel/tty.h>
#include <kernel/panic.h>
#include <stdio.h>
#include <paging.h>
#include <gdt.h>
#include <idt.h>
#include <port.h>
#include <pic.h>
#include <stddef.h>

struct multiboot_header_tag* multiboot_tag = NULL;

void kinit(uint32_t magic, struct multiboot_header_tag* struct_addr) {
  if (magic != MULTIBOOT2_BOOTLOADER_MAGIC)
    printf("[!] OS was loaded using unsupported bootloader. Use carefully.\n");
  else
    multiboot_tag = struct_addr;
  tty_init();
  // Disable IRQs since we need to program PIC first to IRQ not overlap with CPU Exceptions
  
  PIC_remap(0x20, 0x28);
  outb(0x21, 0xFC); // Mask everytihg except Timer IRQ
  outb(0xA1, 0xFF);
  set_gdt_entries();
  set_gdtr();
  init_idt();
  set_idtr();
  init_page_tables();
}