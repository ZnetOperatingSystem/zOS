#ifndef __ZFS_H
#define __ZFS_H
#define BYTESPERBLOCK 512
#define BYTESPERNODE 1024
//#include "node.h"
#include "zfs_block.h"
const char blocksig[] = {0x00,0xAA,0xFF};
const char nodesig[] = {0xFF,0xAA,0x00};
struct zfs{
	struct block *_b;
	struct zfs *next;
};
void _gSize(char *path2dev);
void mkzfs(char *path2dev);
struct dir{
	char sig[1];
	char path[80];
	char cont[1024];
};
void zwrite(char *path2dev);
#endif
