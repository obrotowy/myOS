cd kernel
make clean
cd ../libc
make clean
cd ..
rm rootfs/boot/kernel.elf
rm -r rootfs/include
rm -r rootfs/lib
rm disk.img