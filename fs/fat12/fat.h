#ifndef __FAT_H
#define __FAT_H
typedef struct fat_fs_12{
	unsigned char bootjump[3];
	unsigned char oem_name[8];
	unsigned short bps;
	unsinged char spc;
	unsigned short rsc;
	unsigned char tablecount;
	unsigned short root_ent_count;
	unsigned short ts16;
	unsigned short spt;
	unsigned short hsc;
	unsigned int hisc;
	unsigned int ts32;
	unsigned char es[54];
}fat_fs_12_t;
#endif
