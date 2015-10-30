#include <stdio.h>
#include <string.h>
void call(char *func,char *args){
		//asm("push %esp, offset %P0" : : "m"(args));
		asm("call %P0" : : "m"(func));
		asm("pop %esp");
}
void zsh(){
	t_init();
	kprintf("zOS precompiled shell\n");
	while(1){
		//char *s = malloc(1024);
		char s[80];
		kstrcpy(s,kgets());
		char args[80];
		int i = 0;
		int b = 0;
		while(s[i] != 0){
			if(s[i] == ' ')
				b = 1;
			if(b == 1)
				kstrcat(args,&s[i]);
			i++;
		}
		call(s,args);
	}
}
