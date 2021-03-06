/*
* (C) 2015 Zachary James Schlotman
* Kernel Main
* zos.kernel
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <kernel/tty.h>
#include <zfs.h>
#include "../fs/zfs/zfs.h"
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
int int2str(int i){
	int c = 0;
	char *buf = malloc(80);
	int n;
	int t;
	int inc;
	int bi =  i;
	while(bi > 0){
		t++;
		bi/=10;
	}
	while(i > 0){
		n = (i % 10);
		if(n == 0)
			buf[t - inc] = '0';
		else if(n == 1)
			buf[t - inc] = '1';
		else if(n == 2)
			buf[t - inc] = '2';
		else if(n == 3)
			buf[t - inc] = '3';
		else if(n == 4)
			buf[t - inc] = '4';
		else if(n == 5)
			buf[t - inc] = '5';
		else if(n == 6)
			buf[t - inc] = '6';
		else if(n == 7)
			buf[t - inc] = '7';
		else if(n == 8)
			buf[t - inc] = '8';
		else if(n == 9)
			buf[t - inc] = '9';
		inc++;	
		i/=10;
	}
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
void dump_args(){
	kprintf("Drive Selection:");
	int drive = ddrive();
	if(drive == 0x00)
		kprintf("0/PRIMARY\n");
	else if(drive == 0x01)
		kprintf("0/SECONDARY\n");
	else
		kprintf("Unkown\n");
	kprintf("I/O Port:");
	if(drive == 0x00)
		kprintf("0x1FX\n");
	else if(drive == 0x01)
		kprintf("0x17X\n");
	else
		kprintf("Unkown\n");
	kprintf("ZFS Offset\n");
	int offset = zfs_scan(drive);
	
}
void kernel_main(int a,char *b){
	if(strcmp(b,"s") == 0)
		zsh();
	t_init();
	kprintf("Detecting Hard Drives\n");
	ide_init(0x1F0,0x3f6,0x170,0x376,0x000);
	uint16_t drive;
	if(strcmp(b,"fp") == 0)
		drive = 0x00;
	else
		drive = ddrive();
	kprintf("Detecting Keyboards\n");
	outb(0x60,0xF2);
	kprintf("Initializing Devices\n");
	outb(0x60,0xED);
	outb(0x60,0xEE);
	outb(0x1F0 + 0x02,0);
	outb(0x1F0 + 0x03,0);
	outb(0x1F0 + 0x04,0);
	outb(0x1F0 + 0x05,0);
	//outb(0x1F0 + 0x07,0xEC);
	kprintf("Sent identify to Primary IDE Device\n");
	uint8_t stat = inportb(0x1F0 + 0x07);
	kprintf("Allocating memory for variables\n");
	char cmdbuf;
	kprintf("Testing Disk Drivers\n");
	char buf[80];
	//ata_read_master(buf,0,drive);
	//kprintf("%s\n",buf);
	kprintf("Scanning disk for ZosFS Signature\n");
	int offset;
	if(strcmp(b,"fp") == 0)
		offset = zfs_scan(1);
	else
		offset = zfs_scan(0);
	kprintf("Scanning for end of partition\n");
	int endoffset = zfs_scanend(drive,offset);
	panic();
	kprintf("Mounting Root FileSystem\n");
	zfs_mount(offset,endoffset);
	kprintf("Passing control to init Script\n");
	exec_script("/init.initsh");
}
void kernel_main_old(int a,char *b){
	t_init();
	kprintf("Loading early kernel.\n");
	ide_init(0x1F0, 0x3F6, 0x170, 0x376, 0x000);
	int i = 0;
	int commandnum = 4;
	//char *mtest = malloc(80);
	//kstrcpy(mtest,"test");
	//kprintf("%s\n",mtest);
	char *commands[] = {"ls","help","memlist","echo"};
	kprintf("\nSimple kernel x86\n");
	kprintf("Arguments: %s\n",b);
	kprintf("Initial Runlevel K\n");
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
		
	}
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
		else if(nstrcmp(str,"hlt") == 0){
			kprintf("CPU Halted\n");
			halt();
		}
		else if(nstrcmp(str,"read") == 0){
			i = 0;
			//ide_atapi_read(1,1,1,0,0);
			char *buffer = malloc(1024);
			io_read(0,0,1,buffer);
			kprintf("%s\n",buffer);
			//kprintf("%c\n",ic);
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
