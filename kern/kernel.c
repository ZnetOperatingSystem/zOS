/*
*Outdated kernel main. Used for functions and enums
*(c)2015 Zachary James Schlotman
*/
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <kernel/tty.h>
#include <kernel/vga.h>

enum INPUT_KEYS{
	A = 0x9E,
	B = 0xB0,
	C = 0xAE,
	D = 0xA0,
	E = 0x92,
	F = 0xA1,
	G = 0xA2,
	H = 0xA3,
	I = 0x97,
	J = 0xA4,
	K = 0xA5,
	L = 0xA6,
	M = 0xB2,
	N = 0xB1,
	O = 0x98,
	P = 0x99,
	Q = 0x90,
	R = 0x93,
	S = 0x9F,
	T = 0x94,
	U = 0x96,
	V = 0xAF,
	W = 0x91,
	X = 0xAD,
	Y = 0x95,
	Z = 0xAC,
	NL = 0x1C
};
void keyboard_irq();
char kgetc(){
	int i = 0;
	unsigned char sc;
		sc = inportb(0x60);
		if(sc == A){
			return 'A';
		}
		else if (sc == B){
			return 'B';
		}
		else if (sc == C){
                        return 'C';
                }

		else if (sc == D){
                        return 'D';
                }

		else if (sc == E){
                        return 'E';
                }

		else if (sc == F){
                        return 'F';
                }

		else if (sc == G){
                        return 'G';
                }

		else if (sc == H){
                        return 'H';
                }

		else if (sc == I){
                        return 'I';
                }

		else if (sc == J){
                        return 'J';
                }

		else if (sc == K){
                        return 'K';
                }

		else if (sc == L){
                        return 'L';
                }

		else if (sc == M){
                        return 'M';
                }

		else if (sc == N){
                        return 'N';
                }

		else if (sc == O){
                        return 'O';
                }

		else if (sc == P){
                        return 'P';
                }

		else if (sc == Q){
                        return 'Q';
                }

		else if (sc == R){
                        return 'R';
                }

		else if (sc == S){
                        return 'S';
                }

		else if (sc == T){
                        return 'T';
                }

		else if (sc == U){
                        return 'U';
                }

		else if (sc == V){
                        return 'V';
                }

		else if (sc == W){
                        return 'W';
                }

		else if (sc == X){
                        return 'X';
                }

		else if (sc == Y){
                        return 'Y';
                }

		else if (sc == Z){
                        return 'Z';
                }
		else if(sc == NL){
			return '\n';
		}
		else if(sc == 0x00){
			return '\001';
		}
		else{
			return '\001';
		return '\001';	
	}
}
void putstr(const char *str){

        for(int i = 0; i < strlen(str);i++){
                t_putc(str[i]);
        }

}
char *shell_gets(char *ret){
	char *g = malloc(1024);
	char c;
	char oldc;
	int i1 = 0;
	int i = strlen(g);
	while (1){
		c = kgetc();
		if(c == oldc){
			continue;
		}
		if(c == '\001'){
			continue;
		}
		oldc = c;
		t_putc(kgetc());
		if(c == '\n'){
			break;
		}
		if(inportb(0x60) == NL){
			break;
		}
		g[i] = c;
		i++;
	}
	ret = g;
	t_putc('\n');
	t_putc('>');
	return ret;
}
uint8_t lastkey = 0;
uint8_t *keycache = 0;
uint16_t key_loc = 0;
uint8_t __kbd_enabled = 0;

