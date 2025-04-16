HOST?=i686-elf
ARCH?=i386

CFLAGS?=-O2 -g -pipe
ASFLAGS?=
LDFLAGS?=

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra
ASFLAGS:=$(ASFLAGS)
LDFLAGS:=$(LDFLAGS) -nostdlib -lgcc

ARCHDIR=arch/$(ARCH)

include $(ARCHDIR)/make.config

CFLAGS:=$(CFLAGS) $(KERNEL_ARCH_CFLAGS)
LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
ASFLAGS:=$(ASFLAGS) $(KERNEL_ARCH_ASFLAGS)

KERNEL_OBJS=$(KERNEL_ARCH_OBJS)
OBJS=$(KERNEL_OBJS) kernel/main.o
LINK_LIST=$(OBJS)

.SUFFIXES: .o .c .asm

kernel.elf: $(OBJS) $(ARCHDIR)/linker.ld
	$(CC) -T $(ARCHDIR)/linker.ld -o $@ $(LINK_LIST) $(LDFLAGS)

.asm.o:
	$(AS) $(ASFLAGS) $< -o $@

.c.o:
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm $(OBJS)