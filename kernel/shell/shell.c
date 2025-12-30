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
  uint64_t seconds = ticks / (uint64_t) 18;
  printf("Uptime: %d ticks, %d seconds\n", ticks, seconds);
}