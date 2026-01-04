#pragma once
#include <x86/ps2.h>

static inline void reboot() {
  ps2_send_command(0xFE);
}