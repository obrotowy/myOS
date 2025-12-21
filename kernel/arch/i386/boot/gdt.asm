global gdt
global gdt.code
global gdt.data
global gdt.pointer

section .rodata
  gdt:
    dq 0
    .code: equ $ - gdt
      dq (0xA << 52) | (0x9A << 40) | (0xF << 48) | 0xFFFF
    .data: equ $ - gdt
      dq (0xC << 52) | (0x92 << 40) | (0xF << 48) | 0xFFFF
    .pointer:
      dw $ - gdt - 1
      dq gdt