#pragma once
#include <stdbool.h>
#include <stdint.h>

extern bool check_cpuid_availability();
extern void cpuid_get_vendor(const char* buf);
extern uint32_t get_cr0();
extern uint32_t get_ebx();
extern bool check_long_mode();