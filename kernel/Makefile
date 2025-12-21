CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra --sysroot=$(DESTDIR) -isystem=/include -masm=intel
ASFLAGS:=$(ASFLAGS)
LDFLAGS:=$(LDFLAGS) -nostdlib --sysroot=$(DESTDIR)
INCLUDE:=-Iinclude/

BOOTSTRAP_OBJS=arch/x86/mem/paging.o arch/x86/boot/boot.o arch/x86/cpuid.o arch/x86/tty/tty.o arch/x86/boot/kinit.o arch/x86/gdt/gdt.o arch/x86/idt/idt.o
BOOTSTRAP_INCLUDE=$(INCLUDE) -Iarch/x86/include/

KERNEL_OBJS=kernel/main.o arch/amd64/tty/tty.o

kernel.elf: kernel64.o boot32.o linker.ld
	x86_64-elf-gcc -T linker.ld kernel64.o boot32.o -o $@ $(LDFLAGS) -lk -lgcc
kernel64.o: $(KERNEL_OBJS)
	x86_64-elf-gcc $(KERNEL_OBJS) -o $@ $(INCLUDE) $(LDFLAGS) -lk -lgcc

kernel/%.o: kernel/%.c
	x86_64-elf-gcc -c $< -o $@ $(CFLAGS) $(INCLUDE)

boot32.o: $(BOOTSTRAP_OBJS)
	i686-elf-gcc -o $@ $(BOOTSTRAP_OBJS) $(LDFLAGS)

arch/amd64/%.o: arch/amd64/%.c
	x86_64-elf-gcc -c $< -o $@ $(CFLAGS) $(INCLUDE)

arch/x86/%.o: arch/x86/%.c
	i686-elf-gcc -c $< -o $@ $(CFLAGS) $(BOOTSTRAP_INCLUDE)

arch/x86/%.o: arch/x86/%.asm
	nasm -felf32 $< -o $@ $(ASFLAGS) -Iinclude/

clean:
	rm $(KERNEL_OBJS) $(BOOTSTRAP_OBJS)

install-headers:
	cp -r include/* $(DESTDIR)/include