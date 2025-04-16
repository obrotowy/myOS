cd kernel/
make
cd ..
mv kernel/kernel.elf rootfs/boot/
grub2-mkrescue rootfs -o disk.img