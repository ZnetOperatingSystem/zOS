all:
	$(CC) -c panic.c -o panic.o -nostdlib
	$(CC) -c sleep.c -o sleep.o -nostdlib -ffreestanding -std=gnu99
	$(CC) -c atox.c -o atox.o -nostdlib -I../include
clean:
	rm *.o

