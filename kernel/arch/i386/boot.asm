MBMAGIC         equ 0xE85250D6
ARCH            equ 0
HEADER_LENGTH   equ 16
CHECKSUM        equ -(MBMAGIC + ARCH + HEADER_LENGTH)

section .multiboot
align 4
dd MBMAGIC
dd ARCH
dd HEADER_LENGTH
dd CHECKSUM 

section .text
global _start
_start:
    mov word [0xB8000], 0x4141
    cli
.hang:  hlt
    jmp .hang