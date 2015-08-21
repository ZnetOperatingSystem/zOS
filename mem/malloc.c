/*
* (C) 2015 Zach Schlotman
* ZOS Memory allocator
* ZOS Project
* liballoc
* Probaly broken will provide working i386 binary if it is.
*/
struct page{
	unsigned long size;
	unsigned int startmemory;
	unsigned int endmemory;
	char data[1];
	struct page *next;
	int pos; 
};
int allocated[(1024 * 1024)];
struct page *findpage(struct page *pa,unsigned long esize){
	unsigned long size;
	int startmem = 0x00007E00;
	int maxmem = 0x0007FFFF;
	int i = 0;
	int currentmem = startmem;
	struct page *pg;
	while(1){
		if(size >= esize)
			break;
		else if(allocated[i] != currentmem){
			if(startmem != currentmem){
				//currentmem++;
				break;
			}
			currentmem++;
			size++;
			//printf("Hmm\n");
			allocated[i] = currentmem;
			i++;
			continue;
		}
		else if(currentmem == maxmem){
			return -1;
		}
		else{
			currentmem++;
			continue; 
		}
		i++;
	}
	struct page np;
	
	np.size = size;
	np.startmemory = startmem;
	np.endmemory = currentmem;
	pg = &np;
	pa = pg;
	return pg;
}
struct partialpage{
	struct page *next;
	unsigned long *size;
	unsigned int *startmem;
	unsigned int *endmem;
};
struct combpg{
	struct partialpage *ppg;
	unsigned long size;
	unsigned int *astartmem;
	unsigned int *aendmem;
};
void *malloc(unsigned long ssize){
	unsigned long size = ssize;
	int i = 0;
	unsigned int totalsize = 0;
	struct page *pg;
	struct partialpage *ppg;
	//unsigned int omem = 0x00007E00;
	char ret[size];
	/*while(1){
		findpage(pg);
		if(pg->size >= size)
			return &(pg);
		if(totalsize >= size){

		}
		totalsize+=pg->size;
		ppg->startmem[i] = pg->startmem;
		ppg->endmem[i] = pg->endmem;
		ppg->size[i] = pg->size;
	}*/
	while(1){
		findpage(pg,size);
		if(pg->size >= size){
			struct page tmppg;
			tmppg = *pg;
			tmppg.data[0] = pg->startmemory;
			tmppg.data[1] = pg->endmemory;
			unsigned int start = pg->startmemory;
			int i = 0;
			while(start < pg->endmemory){
				ret[i] = start;
				start++;
				i++;
			}
			return (void*)ret;
		}
		else{
			unsigned int startmem = pg->startmemory;
			struct page tmppg;
			tmppg = *pg;			
			int i = pg->pos;
			while(startmem < pg->endmemory){
				size = (size - 1);
				ret[i] = startmem;
				tmppg.pos++;
				i++;
				startmem++;

			}
		}
	}
}
