#include <x86/ps2.h>
#include <stdbool.h>
#include <kernel/panic.h>

void ps2_init() {
  bool dual_channel = false;
  // Disable devices
  ps2_send_command(0xAD);
  ps2_send_command(0xA7);

  // Flush buffer
  while (ps2_read_status() & PS2_OUTPUT_BUFFER_STATUS_BIT) {
    ps2_read_data();
  }
  // Controller configuration byte
  uint8_t cfg = ps2_get_config();
  cfg &= 0b10101110;
  ps2_send_config(cfg);

  // Perform Controler Self Test
  ps2_send_command(0xAA);
  uint8_t response = ps2_read_data();
  if (response != 0x55)
    panic("PS2 Initialization failed.");
  
  // Determine if there are 2 channels
  ps2_send_command(0xA8);
  cfg = ps2_get_config();
  if (cfg & 0x20)
    puts("[ps2] Single channel controller detected.\n");
  else {
    dual_channel = true;
    puts("[ps2] Dual Channel controller detected.\n");
  }
  // Test interface
  ps2_send_command(0xAB);
  if (ps2_read_data() != 0) 
    panic("First PS/2 Port test failed.");
  if (dual_channel) {
    ps2_send_command(0xA9);
    if (ps2_read_data() != 0)
      panic("Second PS/2 Port test failed.");
  }
  // Enable devices and IRQs
  cfg = ps2_get_config();
  ps2_send_command(0xAE);
  cfg |= 1;
  if (dual_channel) {
    ps2_send_command(0xA8);
    cfg |= 2;
  }
  ps2_send_config(cfg);

  // Reset devices
  ps2_send_data(0xFF);
  printf("[ps2] Device 0 reset response: 0x%X", ps2_read_data());
  while (ps2_read_status() & PS2_OUTPUT_BUFFER_STATUS_BIT)
    printf(" 0x%X", ps2_read_data());
  if (dual_channel) {
    ps2_send_data_second_device(0xFF);
    printf("\n[ps2] Device 1 reset response: 0x%X", ps2_read_data());
    while (ps2_read_status() & PS2_OUTPUT_BUFFER_STATUS_BIT)
    printf(" 0x%X", ps2_read_data());
  }
  putchar('\n');
  while (ps2_read_status() & PS2_OUTPUT_BUFFER_STATUS_BIT)
    ps2_read_data();
}