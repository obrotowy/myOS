#pragma once
#include <ps2.h>

static inline void reboot() {
  ps2_send_command(0xFE);
}