#include <kernel/panic.h>
#include <stdio.h>
#include <x86/ps2.h>


uint64_t ticks = 0;

__attribute__((noreturn))
void exception_handler(void);
void exception_handler() {
    panic("CPU thrown an exception.");
}

void timer_handler(void) {
  ++ticks;
}
