#include <shell/shell.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <kernel/tty.h>
#include <power.h>

extern uint64_t ticks;
extern uint64_t get_available_memory();
extern void parse_multiboot_struct();
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
  else if (strcmp(cmd, "mbinfo") == 0)
    parse_multiboot_struct();
  else if (strcmp(cmd, "meminfo") == 0)
    printf("Available memory: %d MB\n", (int) get_available_memory() >> 20);
  else
    printf("Unrecognized command: %s\n", cmd);
  puts("> ");
}

void uptime() {
  printf("Uptime: %d ticks, %d seconds\n", (int) ticks, (int)ticks/18);
}

