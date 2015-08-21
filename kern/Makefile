CC=i386-elf-gcc
AS=i386-elf-as
NASM=nasm -f elf
all:
	$(CC) -c kmain.c -o kmain.o -nostdlib -I../include -ffreestanding
	$(CC) -c kloader.c -o kloader.o -nostdlib -I../include -ffreestanding
	$(CC) -c kernel.c -o kernel.o -nostdlib -I../include -ffreestanding -std=gnu99
	$(CC) -c tty.c -o tty.o -nostdlib -I../include -ffreestanding -std=gnu99
	$(AS) boot.S -o boot.o
	$(AS) crti.S -o crti.o 
	$(AS) crtn.S -o crtn.o
	$(NASM) inportb.asm -o inportb.o