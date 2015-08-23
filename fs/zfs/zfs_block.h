#ifndef _ZFS_NODE_H
#define _ZFS_NODE_H
#include "zfs.h"
struct block{
	unsigned char sig[2];//3 character signature
	unsigned int max_number_of_dirs;//Maximum number of directories
	unsigned int number_of_dirs;//Number of dirs;
	unsigned int max_number_of_files;//Maximum number of files
	unsigned int numver_of_files;//Number of files;
	struct zfs _z;
	struct block next;
};
#endif
