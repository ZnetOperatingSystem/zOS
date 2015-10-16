
all:
	@echo "CC kprintf.o"
	@$(CC) -c kprintf.c -o kprintf.o -nostdlib -ffreestanding -I../include
	@echo "CC inportsl.o"
	@$(CC) -c inportsl.c -o inportsl.o -nostdlib -ffreestanding -I../include
	@echo "CC io.o"
	@$(CC) -c io.c -o io.o -nostdlib -ffreestanding
clean:
	rm *.o
