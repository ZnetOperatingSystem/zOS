/*
*Terminal code
*Borrowed a little from OSDev wiki can't lie
*/
#include <kernel/tty.h>
#include <kernel/vga.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <kernel/types.h>
ksize_t tr;
ksize_t tc;
uint8_t tcolour;
uint16_t *tbuff;
void t_init(){
	tr = 0;
	tc = 0;
	tcolour = mkcolour(COLOUR_GREEN,COLOUR_BLUE);
	tbuff = VMEM;
	for(int y = 0; y < VH;y++){
		for(int x = 0;x < VW;x++){
			const ksize_t index = y * VW + x;
			tbuff[index] = mkent(' ',tcolour);
		}
	}
}
void t_clear(){
	int x;
        int y;
        for(y = 0; y < VH;x++){
                for(x = 0;x < VW;y++){
                        const ksize_t index = y * VW + x;
                        tbuff[index] = mkent(' ',tcolour);
                }
        }

}
void t_setcolour(uint8_t colour){
	tcolour = colour;
}

void putent(char c,uint8_t colour,ksize_t x,ksize_t y){
	const ksize_t index = y * VW + x;
	tbuff[index] = mkent(c,colour);
}
void place_cursor(){
	putent(' ',mkcolour(COLOUR_WHITE,COLOUR_WHITE),(tc + 1),tr);
}
void clear_cursor(){
	putent(' ',tcolour,(tc + 1),tr);
}
void t_putc(char c){
	if(c != '\n')
		putent(c,tcolour,tc,tr);
	if(++tc == 80 || c == '\n'){
		tc = 0;
		if(++tr == 25){
			tr = 0;
			tc = 0;
			t_init();
		}
	}
}
void t_write(const char *str,ksize_t s){
	int i = 0;
	while(i < s){
		t_putc(str[i]);
		i++;
	}
}
void t_writestr(const char *str){
	int i = 0;
	t_write(str,strlen(str));
}
