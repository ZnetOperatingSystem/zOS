#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "zfs.h"
int __getsize(char *path2dev){
	int dev = open(path2dev,O_RDONLY);
	int ret = 0;
	char *buff = malloc(1024);
	while(read(dev,buff,1) > 0){
		ret++;
	}
	return ret;
}
void mkzfs(char *path2dev){
	int dev = open(path2dev,O_RDWR);
	int i = 0;
	int size =__getsize(path2dev);
	char sig[] = {0x00,0xFF};
	write(dev,sig,2);
	while(i < size){
		int tmp = i;
		//if(!(tmp % 512)){
			//write(dev,blocksig,strlen(blocksig));
		//}
	//	else{
			write(dev,0x00,1);
	//	}
		i++;
	}
}
void usage(){

}
int main(int a,char *b[]){
	if(a != 2)
		usage();
	else{
		printf("Creating %d byte ZFS file system on %s\n",__getsize(b[1]),b[1]);
		mkzfs(b[1]);
	}
}
