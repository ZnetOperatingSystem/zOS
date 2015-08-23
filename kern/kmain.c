/*
* (C) 2015 Zachary James Schlotman
* Kernel Main
* zos.kernel
*/
#include <stdio.h>
#include <stdlib.h>
#include <kernel/tty.h>
unsigned long __strlen(const char *s1){
	int len = 0;
	while(s1[len] != 0)
		len++;
	return len;
}
int nstrcmp(const char *s1,const char *s2){
	int i = 0;
	while(i < __strlen(s1)){
		if(s1[i] == s2[i]){
			//kprintf("%c%c",s1[i],s2[i]);
			i++;
		}
		else{
			return i;
		}
		i++;
	}
	if(i == __strlen(s1)){
		return 0;
	}
	return 0;
}
void kernel_main(int a,char *b){
	t_init();
	int i = 0;
	int commandnum = 4;
	//char *mtest = malloc(80);
	//kstrcpy(mtest,"test");
	//kprintf("%s\n",mtest);
	char *commands[] = {"ls","help","memlist","echo"};
	kprintf("\nSimple kernel x86\n");
	kprintf("Arguments: %s\n",b);
	kprintf("Initial Runlevel 1\n");
	kprintf("Modprobe:");
	//char *str = malloc(1024);
	//kstrcpy(str,b);
	//kprintf("%s\n",str);
	kprintf("Failed!\n");
	kprintf("Begin mount\n");
	//if(strcmp(str,"HLT") == 0){
	//	kprintf("Halting CPU\n");
		//halt();
		
	//}
	if(b[0] == 'P' && b[1] == 'A' && b[2] == 0){
		
	}else
		panic();
	kprintf("Dropping into a shell\n");
	char *str = malloc(80);
	kprintf("$");
	char oldc;
	
	while(1){
		//shell_gets(str);
		int i = 0;
		char c = kgetc();
		if(c == oldc)
			continue;
		if(c == '\001')
			continue;
		oldc = c;
		t_putc(c);
		kstrcat(str,str);
		//kstrcat(str,kgets());
		kstrcat(str,kgetc());
		if(kgetc() != '\n')
		 	continue;
		//str = kgets();
		//kprintf("\n$");
		//while (i < strlen(str)){
			//kprintf("%c",str[i]);
		//	i++;
		//}
		kprintf("%s\n",str);
		//kprintf("%s\n",str);
		if(nstrcmp(str,"LS") == 0){
			kprintf("Mount not implemented\n");
		}
		else if(nstrcmp(str,"HELP") == 0){
			i = 0;
                        while (i < commandnum){
                                kprintf("%s\n",commands[i]);
                                i++;
                        }
		}
		else if(nstrcmp(str,"MEMLIST") == 0){
			i = 0;
			while(i < 524288){
				char c = (char)0x00000001;
				kprintf("%c",c);
				c++;
				i++;
			}
		}
		else{

		}
		kprintf("$");
		str = malloc(1024);
	}
}
