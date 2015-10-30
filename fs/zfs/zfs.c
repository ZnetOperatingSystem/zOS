#include "zfs.h"
#include <stdint.h>
int scan_for_sig(char *buf){
	int i = 0;
	while(i < 256){
		if(buf[i] == 0x26){
			//kprintf("Started\n");
			int i1 = 0;
			if(buf[(i + 1)] == 0x01 && buf[(i + 2)] == 0x03 && buf[(i + 3)] == 0x08)
				i1 = 4;
			if(i1 == 4){
				kprintf("Found Valid ZFS Signature!\n");
				return 1;
			}
		}
		i++;
	}
	return 0;
}
int scan_for_esig(char *buf){
	int i = 0;
	while(i < 256){
		if(buf[i] == 0xAA){
			if(buf[(i + 1)] == 0x11 && buf[(i + 2)] == 0x00 && buf[(i+3)] == 0x01){
				kprintf("Found Full ZFS Disk Partition\n");
				return 1;
			}
		}
		i++;
	}
	return 0;
}
int zfs_scan(int force){
	int i = 0;
	char buf[256];
	uint32_t address = 0x00;
	while(i < 256){
		buf[i] = 0;
		i++;
		
	}
	i = 0;
	int ret = 0;
	uint16_t drive;// = ddrive();
	if(force == 1)
		drive =  0x00;
	else
		drive = ddrive();
	while(1){
		ata_read_master(buf,i,drive);
		kprintf(".");
		//kprintf("%s\n",buf);
		int i2 = 0;
		while(i2 < 256){
			//kprintf("%c",buf[i2]);
			i2++;
		}
		//panic();
		//kprintf("e\n");
		int b =	scan_for_sig(buf);
		if(b == 1)
			return ret;
		int i1 = 0;
		while(i < 256){
			buf[i] = 0;
			i++;
		}
		ret++;
		//buf = malloc(256);
		i++;
	}
	//kprintf("_Exec\n");
	return i;	

}
int zfs_scanend(uint16_t drive,int offset){
	kprintf("Exec\n");
	int i = 0;
	char buf[256];
	kprintf("exec\n");
	int address = offset;
	while(1){
		//kprintf(".");
		if(ata_read_master(buf,address,drive) == -1)
			return -1;
		int b = scan_for_esig(buf);
		if(b == 1)
			break;
		int i1 = 0;
		while(i1 < 256){
			buf[i1] = 0;
			i1++;
		}
		address++;
	}
	return address;
}
zfs_mount(int offset,int end){
	int ba = zfs_scan(0);
	int be = zfs_scanend(0,ba);
	
}
