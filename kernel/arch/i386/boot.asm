MBMAGIC         equ 0xE85250D6
ARCH            equ 0
HEADER_LENGTH   equ 20
CHECKSUM        equ -(MBMAGIC + ARCH + HEADER_LENGTH)
MULTIBOOT_TAG_TYPE_END equ 0

section .multiboot
align 8
dd MBMAGIC
dd ARCH
dd HEADER_LENGTH
dd CHECKSUM 
dd MULTIBOOT_TAG_TYPE_END

section .text
global _start
_start:
    cli
    extern kmain
    call kmain
.hang:  hlt
    jmp .hang