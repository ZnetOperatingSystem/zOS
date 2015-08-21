/*
*(C)2015 Zachary James Schlotman
*ZOS kernel Loader
*zos.kernel
*Used to append args to kernel
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <kernel/tty.h>
void kernel_loader_init(){
	t_init();
}
char *kgets(){
	char *args = malloc(1024);
	char oldc;
	char c;
	int i = 0;
	while(1){
		c = kgetc();
		if(c == oldc)
			continue;
		if(c == '\001')
			continue;
		oldc = kgetc();
		if(c == '\n')
			break;
		if(inportb(0x60) == 0x1C)
			break;
		t_putc(c);
		args[i] = c;
		i++;
		
	}
	 i = 0;
	return args;
}
int countsp(char *s){
	int i = 0;
	int ret = 0;
	while(i < strlen(s)){
		if(s[i] == ' ')
			ret++;
		i++;
	}
	return ret;
}
void kernel_loader_main(){
	kprintf("x86 ZOS Kernel\n");
	kprintf("(c) 2015 Zachary James Schlotman\n");
	kprintf("Libc dist by newlib\n");
	int i = 123;
	kprintf("%d\n",i);
	kprintf("Libk (c) 2015 Zachary James Schlotman\n");
	kprintf("Please Enter Any Arguments to pass to kernel\n");
	kprintf("$>");
	char *s = malloc(1024);
	kstrcpy(s,kgets());
	int hd = (int)0x00000475;
	kernel_main(countsp(s),s);
}
