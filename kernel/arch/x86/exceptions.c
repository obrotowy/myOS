#include <kernel/panic.h>

__attribute__((noreturn))
void exception_handler(void);
void exception_handler() {
    panic("CPU thrown an exception.");
}