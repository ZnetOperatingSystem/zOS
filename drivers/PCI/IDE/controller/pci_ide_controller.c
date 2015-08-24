#include "pci_ide_controller.h"
#include <stdio.h>
#include <stdlib.h>
unsigned long _strlen(const char *str){
	unsigned long ret = 0;
	while(str[ret] != 0)
		ret++;
	return ret;
}
void wait_irq(){
	while(!ide_irq_invoked)
		;
	ide_irq_invoked = 0;
}
void ide_irq(){
	ide_irq_invoked = 1;
}
unsigned char ide_read(unsigned char channel,unsigned char reg){
	unsigned char ret;
	if (reg > 0x07 && reg < 0x0C)
		ide_write(channel,ATA_REG_CONTROL,0x08 | channels[channel].nIEN); 
	if (reg < 0x08)
		ret = inportb(channels[channel].base +reg - 0x00);
	else if(reg < 0x0C)
		ret = inportb(channels[channel].base + reg - 0x06);
	else if (reg < 0x0E)
		ret = inportb(channels[channel].base + reg - 0x0A);
	else if (reg < 0x16)
		ret = inportb(channels[channel].bmide + reg - 0x0E);
	if(reg > 0x07 && reg < 0x0C)
		ide_write(channel,ATA_REG_CONTROL,channels[channel].nIEN);
	return ret;
}
void ide_write(unsigned char channel,unsigned char reg,unsigned char data){
	if (reg > 0x07  && reg < 0x0C)
		ide_write(channel,ATA_REG_CONTROL, 0x80 | channels[channel].nIEN);
	else if(reg < 0x08)
		outportb(channels[channel].base + reg - 0x00,data);
	else if(reg < 0x0C)
		outportb(channels[channel].base + reg - 0x06,data);
	else if(reg < 0x0E)
		outportb(channels[channel].ctrl + reg - 0x0A,data);
	else if(reg < 0x16)
		outportb(channels[channel].bmide + reg - 0x0E,data);
	if(reg > 0x07 && reg < 0x0C)
		ide_write(channel,ATA_REG_CONTROL,channels[channel].nIEN);
}
/*unsigned char *ide_read_buffer(unsigned char channel,unsigned char reg,unsigned int bytestoread){
	unsigned char ret[bytestoread];
	int i = 0;
	while(i < bytestoread){
		ret[i] = ide_read(channel,reg);
		i++;
	}
	return ret;
}*/
//Borrowed from os dev really tired will write my own in future.
unsigned char ide_polling(unsigned char channel, unsigned int advanced_check) {
 
   // (I) Delay 400 nanosecond for BSY to be set:
   // -------------------------------------------------
   for(int i = 0; i < 4; i++)
      ide_read(channel, ATA_REG_ALTSTATUS); // Reading the Alternate Status port wastes 100ns; loop four times.
 
   // (II) Wait for BSY to be cleared:
   // -------------------------------------------------
   while (ide_read(channel, ATA_REG_STATUS) & ATA_SR_BSY)
      ; // Wait for BSY to be zero.
 
   if (advanced_check) {
      unsigned char state = ide_read(channel, ATA_REG_STATUS); // Read Status Register.
 
      // (III) Check For Errors:
      // -------------------------------------------------
      if (state & ATA_SR_ERROR)
         return 2; // Error.
 
      // (IV) Check If Device fault:
      // -------------------------------------------------
      if (state & ATA_SR_DF)
         return 1; // Device Fault.
 
      // (V) Check DRQ:
      // -------------------------------------------------
      // BSY = 0; DF = 0; ERR = 0 so we should check for DRQ now.
      if ((state & ATA_SR_DRQ) == 0)
         return 3; // DRQ should be set
 
   }
 
   return 0; // No Error.
 
}
//End Borrowed
void print_error(){
	kprintf("OH SHIT I/O Error!\nPanicing\n");
	panic();
}

void ide_init(unsigned int BAR0, unsigned int BAR1, unsigned int BAR2, unsigned int BAR3,unsigned int BAR4){
	int j,k,cnt = 0;
	channels[ATA_PRIMARY].base = (BAR0 & 0xFFFFFFFC) + 0x1F0 * (!BAR0);
	channels[ATA_PRIMARY].ctrl = (BAR1 & 0xFFFFFFFC) + 0x3F6 * (!BAR1);
	channels[ATA_SECONDARY].base = (BAR2 & 0xFFFFFFFC) + 0x170 *(!BAR2);
	channels[ATA_SECONDARY].ctrl = (BAR3 & 0xFFFFFFFC) + 0x376 * (!BAR3);
	channels[ATA_PRIMARY].bmide = (BAR4 & 0xFFFFFFFC) + 0;
	channels[ATA_SECONDARY].bmide = (BAR4 & 0xFFFFFFFC) + 8;
	ide_write(ATA_PRIMARY,ATA_REG_CONTROL,2);
	ide_write(ATA_SECONDARY,ATA_REG_CONTROL,2); 
}
void ide_atapi_read(unsigned char drive,unsigned int lba,unsigned char numsects,unsigned short selector,unsigned int edi){
	unsigned int channel = ide_devices[drive].Channel;
	unsigned int slavebit = ide_devices[drive].Drive;
	unsigned int bus = channels[channel].base;
	unsigned int words = 1024;
	unsigned char err;
	int i;
	ide_write(channel,ATA_REG_CONTROL,channels[channel].nIEN = ide_irq_invoked = 0x0);
	atapi_packet[0] = ATAPI_CMD_READ;
	atapi_packet[1] = 0x0;
	atapi_packet[2] = (lba >> 24) & 0xFF;
	atapi_packet[3] = (lba >> 16) & 0xFF;
	atapi_packet[4] = (lba >> 8) & 0xFF;
	atapi_packet[5] = (lba >> 0) & 0xFF;
	atapi_packet[6] = 0x00;
        atapi_packet[7] = 0x00;
        atapi_packet[8] = 0x00;
        atapi_packet[9] = numsects;
        atapi_packet[10] = 0x00;
        atapi_packet[11] = 0x00;
	ide_write(channel,ATA_REG_HDDEVSEL,slavebit << 4);
	i = 0;
	while(i < 4)
		i++;
	ide_read(channel,ATA_REG_ALTSTATUS);
	ide_write(channel, ATA_REG_FEATURES, 0);
	ide_write(channel,ATA_REG_LBA1,(words * 2) & 0xFF);
	ide_write(channel,ATA_REG_LBA2,(words * 2) >> 8);
	ide_write(channel,ATA_REG_COMMAND,ATA_CMD_PACKET);
	if(err = ide_polling(channel,1)) return err;
	asm("rep   outsw" : : "c"(6), "d"(bus), "S"(atapi_packet));
	i = 0;
	while (i < numsects){
		//wait_irq();
		if(err = ide_polling(channel,1)) return err;
		asm("pushw %es");
      		asm("mov %%ax, %%es"::"a"(selector));
      		asm("rep insw"::"c"(words), "d"(bus), "D"(edi));
		asm("popw %es");
		edi +=(words *2);
		i++;
	}
	//wait_irq();
	while (ide_read(channel, ATA_REG_STATUS) & (ATA_SR_BSY | ATA_SR_DRQ))
	      ;
	return 0;
}
void ide_read_sectors(unsigned int drive,unsigned int lba,unsigned int edi, unsigned short es, unsigned char numsects){
	
}
