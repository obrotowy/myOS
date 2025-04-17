HOST?=i686-elf
ARCH?=i386

CC?=$(HOST)-gcc
CXX?=$(HOST)-g++
AS?=$(HOST)-as
AR?=$(HOST)-ar

CFLAGS?=-O2 -g
CXXFLAGS?=$(CFLAGS)
LDFLAGS?=
LIBS?=

DESTDIR?=rootfs
INCLUDEDIR?=$(DESTDIR)/include
LIBDIR?=$(DESTDIR)/lib

COMMON_FLAGS:=--sysroot=$(DESTDIR) -isystem=/include
CFLAGS:=$(CFLAGS) $(COMMON_FLAGS) -ffreestanding -Wall -Wextra
CXXFLAGS:=$(CXXFLAGS) $(COMMON_FLAGS) -Iinclude -fno-exceptions -fno-rtti -D__is_libc -Iinclude
LIBK_CFLAGS:=$(CFLAGS) $(COMMON_FLAGS) -D__is_libk
LIBK_CXXFLAGS:=$(CXXFLAGS) $(COMMON_FLAGS) -D__is_libk

ARCHDIR=arch/$(ARCH)

include $(ARCHDIR)/make.config

CFLAGS:=$(CFLAGS) $(ARCH_CFLAGS)
CXXFLAGS:=$(CXXFLAGS) $(ARCH_CFLAGS)
LIBK_CFLAGS:=$(LIBK_CFLAGS) $(KERNEL_ARCH_CFLAGS)
LIBK_CXXFLAGS:=$(LIBK_CXXFLAGS) $(KERNEL_ARCH_CXXFLAGS)

FREEOBJS=\
$(ARCH_FREEOBJS) \
string/strlen.o \
string/memmove.o \
string/memcpy.o \
string/memset.o \
string/memcmp.o \
stdio/putchar.o \
stdio/puts.o \
stdio/printf.o \
stdlib/itoa.o \

HOSTEDOJBS=$(ARCH_HOSTEDOBJS)

OBJS=$(FREEOBJS) $(HOSTEDOJBS)

LIBK_OBJS=$(FREEOBJS:.o=.libk.o)

BINARIES=libk.a

.PHONY: all clean install install-headers install-libs
.SUFFIXES: .o .libk.o .c .S .cpp

all: $(BINARIES)

libc.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

libk.a: $(LIBK_OBJS)
	$(AR) rcs $@ $(LIBK_OBJS)

.c.o:
	$(CC) -c $< -o $@ $(CFLAGS)

.cpp.o:
	$(CXX) -c $< -o $@ $(CXXFLAGS)

.S.o:
	$(CC) -c $< -o $@ $(CFLAGS)

.c.libk.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(LIBK_CFLAGS)

.S.libk.o:
	$(CC) -MD -c $< -o $@ $(LIBK_CFLAGS)

clean:
	rm -f $(BINARIES) *.a
	rm -f $(BOJS) $(LIBK_OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) $(LIBK_OBJS:.o=.d) *.d */*.d */*/*.d

install: install-headers install-libs

install-headers:
	mkdir -p $(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(INCLUDEDIR)/.

install-libs: $(BINARIES)
	mkdir -p $(LIBDIR)
	cp $(BINARIES) $(LIBDIR)

-include $(OBJS:.o=.d)
-include $(LIBK_OBJS:.o=.d)