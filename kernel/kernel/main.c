#include <kernel/tty.h>
#include <cpuid.h>
void kmain() {
    tty_init();
    tty_puts("CPU Vendor: ");
    cpuid_get_vendor();
}