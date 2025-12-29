#include <kernel/panic.h>
#include <stdio.h>

__attribute__((noreturn))
void exception_handler(void);
void exception_handler() {
    panic("CPU thrown an exception.");
}

void timer_handler(void) {
  printf("Timer interrupt occured.");
}