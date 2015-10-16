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
#include <kernel/vga.h>
void kernel_loader_init(){
	t_init();
}
void *fmalloc(unsigned long s){
	char ret[s];
	return (void *)ret;
}
char *kgets(){
	char *args =fmalloc(80);
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
	//malloc_init();
	/*int i = 0;
	while(i < 4){
		int i1 = 0;
		while(i1 < 25){
			t_cputc(' ',COLOUR_BLUE);
			++i1;
		}
		i++;
	}
	i = 0;
	while(i < 25){
		t_cputc(' ',COLOUR_WHITE);
		i++;
	}
	i = 0;
	while(i < 23){
		t_cputc(' ',COLOUR_BLUE);
		i++;	
	}
	t_cputc(' ',COLOUR_WHITE);
	t_cputc(' ',COLOUR_BLUE);*/
	/*kprintf("x86 Simple Kernel\n");
	kprintf("(c) 2015 Zachary James Schlotman\n");
	kprintf("Libc dist by newlib\n");
	kprintf("%d\n",i);
	kprintf("Libk (c) 2015 Zachary James Schlotman\n");*/
	kprintf("Znet Operating System Open Source\n(c)2015 Zachary James Schlotman\n\n\n");
	kprintf("Please Enter Any Arguments to pass to kernel\n");
	kprintf("$>");

	char s[80];
	kstrcpy(s,kgets());
	//int hd = (int)0x00000475;
	kernel_main(countsp(s),s);
}
