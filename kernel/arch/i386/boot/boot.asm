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
    call kinit
    mov eax, PML4
    mov cr3, eax
    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax
    call kmain
.hang:  hlt
    jmp .hang

align 4096
PML4:
  dq PDPT + 3
  times 511 dq 0

PDPT:
  dq PDT + 3
  times 511 dq 0

PDT:
  dq 3 | (1 << 7)
  times 511 dq 0