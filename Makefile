CROSS=i386-elf-
CC=$(CROSS)-gcc
CXX=$(CROSS)-g++
CFLAGS="-nostdlib -Iinclude -ffreestanding"
CXXFLAGS=$(CFLAGS)
LDFLAGS="-nostdlib"
all:
	make -C kern
	make -C io
	make -C mem
	make -C lib
	make -C str
	make -C drivers
	i386-elf-gcc */*.o drivers/PCI/IDE/controller/*.o -o simp.kernel -T linker.ld  -nostdlib -ffreestanding
