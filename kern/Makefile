
NASM=nasm -f elf

all:
	@echo "CC kmain.o"
	@$(CC) -c kmain.c -o kmain.o -nostdlib -I../include -ffreestanding -std=gnu99 -I../fs/zfs
	@echo "CC kloader.o"
	@$(CC) -c kloader.c -o kloader.o -nostdlib -I../include -ffreestanding
	@echo "CC kernel.o"
	@$(CC) -c kernel.c -o kernel.o -nostdlib -I../include -ffreestanding -std=gnu99
	@echo "CC tty.o"
	@$(CC) -c tty.c -o tty.o -nostdlib -I../include -ffreestanding -std=gnu99
	@echo "AS boot.o"
	@$(AS) boot.S -o boot.o
	@echo "AS crti.o"
	@$(AS) crti.S -o crti.o 
	@echo "AS crtn.o"
	@$(AS) crtn.S -o crtn.o
	@echo "AS halt.o"
	@$(AS) halt.S -o halt.o
	@echo "NASM inportb.o"
	@echo "CC init.o"
	@$(CC) -c init.c -o init.o
	@$(NASM) inportb.asm -o inportb.o
	@echo "CC xc.o"
	@$(CC)  -c xw.c -o xw.o -nostdlib -I../include -ffreestanding
	@echo "CC panic.o"
	@$(CC) -c panic.c -o panic.o -nostdlib -I../include -ffreestanding
	@echo "AS bootl.o"
	@$(NASM) bootl.asm -o bootl.o
clean:
	rm *.o
