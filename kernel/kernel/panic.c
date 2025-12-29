#include <stdio.h>
#include <stdint.h>

void panic(const char* msg) {
  printf("[PANIC] %s", msg);
  __asm__ volatile ("cli; hlt");
}