#include <x86/pic.h>
#include <x86/port.h>

void PIC_sendEOI(uint8_t irq) {
  if (irq >= 8)
    outb(PIC2_COMMAND, PIC_EOI);
  outb(PIC1_COMMAND, PIC_EOI);
}

void PIC_remap(int offset1, int offset2) {
  // Maps IRQ0-7 to offset1...offset1+7
  // and IRQ8-15 to offset2...offset2+7
  // Where offset is index of element in IDT
  // It is needed since IDT[0] - IDT[0x1F] are reserved for CPU exceptions
  outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outb(PIC1_DATA, offset1);
	io_wait();
	outb(PIC2_DATA, offset2);
	io_wait();
	outb(PIC1_DATA, 1 << CASCADE_IRQ);
	io_wait();
	outb(PIC2_DATA, 2);
	io_wait();
	
	outb(PIC1_DATA, ICW4_8086);
	io_wait();
	outb(PIC2_DATA, ICW4_8086);
	io_wait();
}