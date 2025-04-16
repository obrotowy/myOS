#include <stdint.h>

void kmain() {
    uint16_t* vga_buf = (uint16_t*) 0xB8000;
    *vga_buf = 0x4141;
}