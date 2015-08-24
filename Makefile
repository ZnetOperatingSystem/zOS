CROSS=i386-elf-
CC=$(CROSS)gcc
CXX=$(CROSS)g++
AS=$(CROSS)as
CFLAGS="-nostdlib -Iinclude -ffreestanding"
CXXFLAGS=$(CFLAGS)
LDFLAGS="-nostdlib"
export CC CXX AS CFLAGS CXXFLLAGS LDFLAGS
all:
	make -C kern
	make -C io
	make -C mem
	make -C lib
	make -C str
	make -C drivers
	x86_64-elf-gcc -c bootstrap.S -o bootstrap.o 
	$(CROSS)gcc  */*.o drivers/PCI/IDE/controller/*.o -o simp.kernel   -nostdlib -ffreestanding -T linker.ld
