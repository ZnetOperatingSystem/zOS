void inportsl(unsigned short _port,unsigned long *_buff,unsigned _len){
	int i = 0;
	while(i < _len){
		unsigned long o = inportb(_port);
		_buff[i] = o;
		i++;
	}
}

void insl(unsigned short _port,unsigned long *_buff,unsigned _len){
        asm("cld; rep; insl" :: "D" (_buff), "d" (_port), "c" (_len));
}
