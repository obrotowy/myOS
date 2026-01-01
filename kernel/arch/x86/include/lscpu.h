#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef struct cpu_info_t {
  uint8_t stepping;
  uint8_t model;
  uint16_t family;
} cpu_info_t;

uint32_t get_vendor_id(char* buf);
bool get_cpu_name(char* buf);
void get_cpu_info(cpu_info_t* output);
void lscpu();