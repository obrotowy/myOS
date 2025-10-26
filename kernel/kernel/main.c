#include <kernel/tty.h>
#include <cpuid.h>
#include <stdio.h>
#include <kb.h>

void kmain() {
    puts("[+] System fully loaded.\n");
    printf("CR0: %X\n", get_cr0());
}