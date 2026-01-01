#include <cpuid.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <lscpu.h>

uint32_t get_vendor_id(char* buf) {
  uint32_t max_level = 0;
  uint32_t* ptr = (uint32_t*) buf;
  __cpuid(0, max_level, *ptr, ptr[2], ptr[1]);
  buf[12] = 0;
  return max_level;
}

bool get_cpu_name(char* buf) {
  uint32_t eax = 0;
  __cpuid(0x80000000, eax, *buf, *buf, *buf);
  if (eax < 0x8000004)
  return false;
  uint32_t* ptr = (uint32_t*) buf;
  __cpuid(0x80000002, *ptr, ptr[1], ptr[2], ptr[3]);
  __cpuid(0x80000003, ptr[4], ptr[5], ptr[6], ptr[7]);
  __cpuid(0x80000004, ptr[8], ptr[9], ptr[10], ptr[11]);
  return true;
}

void get_cpu_info(cpu_info_t* output) {
  uint32_t eax, ebx, ecx, edx;
  __cpuid(1, eax, ebx, ecx, edx);
  output->stepping = eax & 0xF;
  output->family = (eax >> 8) & 0xF;
  if (output->family == 6 || output->family == 15)
    output->model = ((eax >> 4) & 0xF) + ((eax >> 20) & 0xFF << 4);
  else
    output->model = (eax >> 4) & 0xF;
  if (output->family == 15)
    output->family += (eax >> 20) & 0xFF;
}

void lscpu() {
  /* TODO: Add CPUID availability check */
  char vendor_string[13];
  uint32_t max_cpuid_level = get_vendor_id(vendor_string);

  char cpu_name[49];
  bool cpu_name_available = get_cpu_name(cpu_name);
  printf("Vendor ID: %s\n", vendor_string);
  puts("Model Name: ");
  if (cpu_name_available)
    printf("%s\n", cpu_name);
  else
    puts("Unknown\n");
  if (max_cpuid_level >= 0x1) {
    cpu_info_t cpu_info;
    get_cpu_info(&cpu_info);
    printf("CPU Family: %d\n", cpu_info.model);
    printf("Model: %d\n", cpu_info.model);
    printf("Stepping: %d\n", cpu_info.stepping);
  }
}