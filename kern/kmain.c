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
int char2int(char c){
	if(c == 'a')
		return 0;
	else if(c == 'b')
		return 1;
	else if(c == 'c')
		return 2;
	else if(c == 'd')
		return 3;
	else if(c == 'e')
		return 4;
        else if(c == 'f')
                return 5;

        else if(c == 'g')
                return 6;

        else if(c == 'h')
                return 7;

        else if(c == 'i')
                return 8;

        else if(c == 'j')
                return 9;

        else if(c == 'k')
                return 10;

        else if(c == 'l')
                return 11;

        else if(c == 'm')
                return 12;

        else if(c == 'n')
                return 13;

        else if(c == 'o')
                return 14;

        else if(c == 'p')
                return 15;

        else if(c == 'q')
                return 16;

        else if(c == 'r')
                return 17;

        else if(c == 's')
                return 18;

        else if(c == 't')
                return 19;

        else if(c == 'u')
                return 20;

        else if(c == 'v')
                return 21;

        else if(c == 'w')
                return 22;

        else if(c == 'x')
                return 23;

        else if(c == 'y')
                return 24;

        else if(c == 'z')
                return 25;
	else if(c == '1')
		return 26;
	else if(c == '2')
                return 27;

	else if(c == '3')
                return 28;

	else if(c == '4')
                return 29;

	else if(c == '5')
                return 30;

	else if(c == '6')
                return 31;

	else if(c == '7')
                return 32;

	else if(c == '8')
                return 33;

	else if(c == '9')
                return 34;

	else if(c == '0')
                return 35;
	else
		return -1;


}
int nstrcmp(const char *s1,const char *s2){
	int i = 0;
	if(strlen(s1) != strlen(s2))
		return -2;
	while(i < strlen(s1)){
		if(s1[i] != s2[i])
			return (i+1);
		i++;
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
	if(b[0] == 'p' && b[1] == 'a' && b[2] == 0){
		
	}else
		panic();
	kprintf("Dropping into a shell\n");
	char *str = malloc(80);
	kprintf("$");
	char oldc;
	//kprintf("%s\n",str);
	i = 0;
	while(1){
		//shell_gets(str);
		char c = kgetc();
		if(c == '\001')
			continue;
		if(c == oldc)
			continue;
		oldc = c;
		t_putc(c);
		if(c != '\n'){
			str[i] = c;
			i++;
		}
		if(c != '\n')
			continue;
		if(nstrcmp(str,"ls") == 0){
			kprintf("Mount not implemented\n");
		}
		else if(nstrcmp(str,"help") == 0){
			i = 0;
                        while (i < commandnum){
                                kprintf("%s\n",commands[i]);
                                i++;
                        }
		}
		else if(nstrcmp(str,"memlist") == 0){
			i = 0;
			while(i < 524288){
				char c = (char)0x00000001;
				kprintf("%c",c);
				c++;
				i++;
			}
		}
		else if(nstrcmp(str,"echo") == 0){
			kprintf("%s\n",str);
		}
		else{
			kprintf("Command not found\n");
		}
		kprintf("$");
		str = malloc(80);
		str[0] = '\0';
		i = 0;
		c = 0;
		for(int i = 0; i < 80; i++){
			str[i] = '\0';
		}		
	}
}
