#include <kernel/tty.h>
#include <cpuid.h>
#include <stdio.h>
#include <ps2.h>

void kmain() {
  puts("[+] System fully loaded.\n");
  printf("CR0: %X\n", get_cr0());
  while (1) {
    printf("%X", ps2_read_data());
  }
}