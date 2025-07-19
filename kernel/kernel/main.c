#include <kernel/tty.h>
#include <cpuid.h>
#include <stdio.h>

void kmain() {
    tty_init();
    puts("[+] kmain()\n");
    if (check_cpuid_availability()) {
        puts("[+] CPUID is available\n");
        char cpu_vendor[14];
        cpuid_get_vendor((char*) cpu_vendor);
        printf("CPU Vendor: %s\n", (char*) cpu_vendor);
    }
    else {
        puts("[-] CPUID is not available\n");
    }
    printf("CR0: %X\n", get_cr0());
}