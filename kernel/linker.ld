ENTRY(_start)

SECTIONS {
  . = 1M;
  .text : ALIGN(4K) {
    boot32.o(.multiboot)
    boot32.o(.text)
  }

  . = 2M;

  .text BLOCK(4K) : ALIGN(4K) {
    kernel64.o(.text)
  }

  .bss : ALIGN(4K) {
    kernel64.o(.bss)
  }
}