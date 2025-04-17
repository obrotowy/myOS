export DESTDIR=$(pwd)/rootfs

cd libc
make install-headers
cd ../kernel
make install-headers
cd ../libc
make install
cd ../kernel
make install
cd ..
grub2-mkrescue -o disk.img rootfs