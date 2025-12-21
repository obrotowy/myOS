%include 'boot/multiboot.inc'

HEADER_LENGTH equ header_end - header_start

section .multiboot
align 8
header_start:
  dd MULTIBOOT_MAGIC_BYTES
  dd MULTIBOOT_ARCH_I386
  dd HEADER_LENGTH
  dd -(MULTIBOOT_MAGIC_BYTES + MULTIBOOT_ARCH_I386 + HEADER_LENGTH)
  dd MULTIBOOT_TAG_TYPE_END
header_end:



section .text
global _start
extern kinit

_start:
  cli
  call kinit
  jmp 0x8:enter_long_mode

enter_long_mode:
  xor ax, ax
  mov cs, ax
  mov ss, ax
  mov ds, ax
  mov es, ax
  jmp 0x200000
  call kmain

.hang:  hlt
  jmp .hang
