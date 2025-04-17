HOST?=i686-elf
ARCH?=i386

CFLAGS?=-O2 -g -pipe
ASFLAGS?=
LDFLAGS?=

CC?=$(HOST)-gcc
AS?=nasm

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra --sysroot=$(DESTDIR) -isystem=/include
ASFLAGS:=$(ASFLAGS)
LDFLAGS:=$(LDFLAGS) -nostdlib -lgcc -lk --sysroot=$(DESTDIR)

ARCHDIR=arch/$(ARCH)
INCLUDE=-Iinclude
include $(ARCHDIR)/make.config

CFLAGS:=$(CFLAGS) $(KERNEL_ARCH_CFLAGS)
LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
ASFLAGS:=$(ASFLAGS) $(KERNEL_ARCH_ASFLAGS)

KERNEL_OBJS=$(KERNEL_ARCH_OBJS)
OBJS=$(KERNEL_OBJS) kernel/main.o
INCLUDE:=$(INCLUDE) $(KERNEL_ARCH_INCLUDE)
LINK_LIST=$(OBJS)

.SUFFIXES: .o .c .asm

kernel.elf: $(OBJS) $(ARCHDIR)/linker.ld
	$(CC) -T $(ARCHDIR)/linker.ld -o $@ $(LINK_LIST) $(LDFLAGS)

.asm.o:
	$(AS) $(ASFLAGS) $< -o $@ $(INCLUDE)

.c.o:
	$(CC) -c $< -o $@ $(INCLUDE) $(CFLAGS)

clean:
	rm $(OBJS)

install: kernel.elf install-headers
	mkdir -p $(DESTDIR)/boot
	cp kernel.elf $(DESTDIR)/boot/kernel.elf

install-headers:
	mkdir -p $(DESTDIR)/include
	cp -r include/* $(DESTDIR)/include