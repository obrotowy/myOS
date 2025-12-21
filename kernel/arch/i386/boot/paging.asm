extern error

global init_page_tables
global enable_paging
init_page_tables:
  ; Map PML4
  mov eax, PDPT
  or eax, 0b11
  mov [PML4], eax
  ; Map PDPT
  mov eax, PDT
  or eax, 0b11
  mov [PDPT], eax
  ; Init huge PDT
  mov ecx, 0
  ; Identity map first 1GB
  .map_pdt:
    mov eax, 0x200000
    mul ecx
    or eax, 0b10000011
    mov [PDT + ecx*8], eax
    inc ecx
    cmp ecx, 512
    jne .map_pdt
  ret

enable_paging:
  mov eax, PDPT
  mov cr3, eax
  mov eax, cr0
  or eax, 1 << 31
  mov cr0, eax

  mov eax, cr0
  test eax, 1 << 31
  jz .paging_failed
  ret
  .paging_failed:
    mov al, "4"
    jmp error

section .bss
  PML4:
    resq 512

  PDPT:
    resq 512

  PDT:
    resq 512