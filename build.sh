export DESTDIR=$(pwd)/rootfs

cd libc
make install-headers
cd ../kernel
make install-headers
cd ../libc
make -j${nproc} install
cd ../kernel
make -j${nproc} install
cd ..
mkdir rootfs/boot/grub/
cp grub.cfg rootfs/boot/grub/grub.cfg
grub2-mkrescue -o disk.img rootfs