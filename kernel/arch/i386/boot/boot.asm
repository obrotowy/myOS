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
global error
extern gdt
extern gdt.pointer
extern init_page_tables
extern check_multiboot
extern check_cpuid_availability
extern check_long_mode
extern set_pae
extern set_lme
extern enable_paging
extern kmain
bits 32
_start:
  cli
  mov esp, stack_top
  call check_multiboot
  call check_cpuid_availability
  call check_long_mode
  call set_pae
  call set_lme
  call init_page_tables
  call enable_paging
  lgdt [gdt.pointer]
  jmp 0x8:long_mode
  .hang:  hlt
    jmp .hang


error:
    mov dword [0xb8000], 0x4f524f45
    mov dword [0xb8004], 0x4f3a4f52
    mov dword [0xb8008], 0x4f204f20
    mov byte  [0xb800a], al
    hlt

bits 64
long_mode:
  xor ax, ax
  mov ss, ax
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  call kmain

section .bss
align 4096

stack_bottom:
    resb 64
stack_top: