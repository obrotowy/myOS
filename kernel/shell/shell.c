#include <shell/shell.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

extern uint64_t ticks;

void uptime();

void shell_exec(const char* cmd) {
  if (strcmp(cmd, "uptime") == 0)
    uptime();
  else
    printf("Unrecognized command: %s\n", cmd);
}

void uptime() {
  printf("Uptime: %d ticks, %d seconds\n", (int) ticks, (int)ticks/18);
}
