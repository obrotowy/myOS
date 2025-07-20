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
extern identity_map
extern fill_page_tables
_start:
    ;setup stack
    mov esp, stack_top

    ; fill page tables using identity map
    push page_table
    call fill_page_tables
    add esp, 4

    ; identity map first 1MB
    push 0x100000
    push 0
    push page_directory
    push page_table
    call identity_map
    add esp, 16
    
    ; map kernel to 0xC000000
    table_768 equ page_directory + 4*768
    mov ebx, 0x100000
    .fill_table:
        mov ecx, ebx
        or ecx, 3
        mov [table_768+eax*4], ecx

    ; enable paging
    mov eax, page_directory
    mov cr3, eax
    
    mov eax, cr0
    or eax, 0x80000001
    mov cr0, eax
    ; setup GDT
    setup_gdt:
    lgdt [GDT_addr]
    jmp dword 0x08:.reload_segments
    .reload_segments:
        mov ax, 0x10
        mov ds, ax
        mov es, ax
        mov fs, ax
        mov gs, ax
        mov ss, ax

    ; call kmain()
    extern kmain
    call kmain
    cli
.hang:  hlt
    jmp .hang


stack_bottom:
    resb 4096
stack_top:

align 4096
page_directory:
    resb 4096
page_table:
    resb 4096

GDT_addr:
dw (GDT_end - GDT) - 1
dd GDT

; GLOBAL DESCRIPTOR TABLE 32-BIT
GDT:

    ; Null segment
    dq 0

    ; Code segment
    dd 0xffff  ; segment limit
    dd (10 << 8) | (1 << 12) | (1 << 15) | (0xf << 16) | (1 << 22) | (1 << 23)

    ; Data segment
    dd 0xffff  ; segment limit
    dd (2 << 8) | (1 << 12) | (1 << 15) | (0xf << 16) | (1 << 22) | (1 << 23)


GDT_end:
