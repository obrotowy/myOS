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
extern lmain
global _start
_start:
  cli
  mov esp, stack_top
  mov ebp, stack_top
  push ebx
  call lmain
  
.hang:  hlt
  jmp .hang


section .bss
  stack_top:
    resb 4096
  stack_bottom:
    db 0xCC