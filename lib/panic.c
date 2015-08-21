void panic(){
	kprintf("A fatal error has been encountered in the kernel. Panic has been called\n");
	kprintf("panic()\n");
	while(1){ }
}
