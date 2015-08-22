#include <stdio.h>
int main(){
	int i = 0;
	int mem = 0x0000;
	while(mem < 0x7c00){
		printf("%c",mem);
		mem++;
	}
}
