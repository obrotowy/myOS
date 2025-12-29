#include <kernel/panic.h>
#include <stdio.h>
#include <ps2.h>


static uint64_t ticks = 0;

__attribute__((noreturn))
void exception_handler(void);
void exception_handler() {
    panic("CPU thrown an exception.");
}

void timer_handler(void) {
  ++ticks;
}

void kb_handler(void) {
  printf("%X ", ps2_read_data());
}