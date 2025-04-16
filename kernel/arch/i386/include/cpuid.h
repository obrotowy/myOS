#pragma once
#include <stdbool.h>

extern bool check_cpuid_availability();
extern const char* cpuid_get_vendor();
extern bool check_paging();