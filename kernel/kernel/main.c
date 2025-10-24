#include <kernel/tty.h>
#include <cpuid.h>
#include <stdio.h>
#include <kb.h>

void kmain() {
    puts("[+] System fully loaded.\n");
    while (1) {
      uint8_t sc = get_scancode();
      if (sc != 0) {
        printf("%X\n", sc);
      }
    }
}