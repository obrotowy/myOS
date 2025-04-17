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

section .bss
stack_bottom:
    resb 4096
stack_top:
section .text
global _start
_start:
    mov esp, stack_top
    extern kmain
    call kmain
    cli
.hang:  hlt
    jmp .hang