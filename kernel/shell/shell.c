#include <shell/shell.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <kernel/tty.h>
#include <power.h>

extern uint64_t ticks;

void uptime();

void shell_exec(const char* cmd) {
  if (strcmp(cmd, "uptime") == 0)
    uptime();
  else if (strcmp(cmd, "clear") == 0)
    tty_clear();
  else if (strcmp(cmd, "lscpu") == 0) {
    lscpu();
  }
  else if (strcmp(cmd, "reboot") == 0)
    reboot();
  else
    printf("Unrecognized command: %s\n", cmd);
  puts("> ");
}

void uptime() {
  printf("Uptime: %d ticks, %d seconds\n", (int) ticks, (int)ticks/18);
}

