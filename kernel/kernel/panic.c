#include <stdio.h>
#include <stdint.h>

void panic(const char* msg) {
  puts("[PANIC] ");
  puts(msg);

  uint32_t eax;
  asm(
    "nop;"
    : "=r"(eax)
    :
  );
  printf("EAX: %X", eax);
  while (1) {
    asm("hlt"
    :
    :);
  }
}