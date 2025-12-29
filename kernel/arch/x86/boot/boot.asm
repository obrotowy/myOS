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
extern kmain
_start:
  cli
  mov esp, stack_top
  mov ebp, esp
  call kinit
  jmp 0x8:reload_segment_registers
  reload_segment_registers:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
  call kmain
.hang:  hlt
  jmp .hang

section .bss
align 4096
  stack_bottom:
    resb 4096
  stack_top:

