// p84.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

int hist[40];
int step;
int curr;
int cons_doub;

int cc_cards[16];
int ch_cards[16];
int cc_pos;
int ch_pos;

enum squares {
	GO,A1,CC1,A2,T1,R1,B1,CH1,B2,B3,
	JAIL,C1,U1,C2,C3,R2,D1,CC2,D2,D3,
	FP,E1,CH2,E2,E3,R3,F1,F2,U2,F3,
	G2J,G1,G2,CC3,G3,R4,CH3,H1,T2,H2,
	NR,NU,BACK3
};

char sq_names[40][5] = {
	"GO","A1","CC1","A2","T1","R1","B1","CH1","B2","B3",
	"JAIL","C1","U1","C2","C3","R2","D1","CC2","D2","D3",
	"FP","E1","CH2","E2","E3","R3","F1","F2","U2","F3",
	"G2J","G1","G2","CC3","G3","R4","CH3","H1","T2","H2"
};

void init(){
	int i,j,k;

	// seed random var
	srand(1);

	for(i=0; i<40; i++){
		hist[i] = 0;
	}
	hist[GO] = 1;

	step = 1;
	curr = 0;
	cons_doub = 0;

	// community chest cards
	for(i=0; i<16; i++){
		cc_cards[i] = -1;
	}
	
	i = rand()%16;
	cc_cards[i] = GO;

	i = rand()%16;
	while(cc_cards[i]!=-1){
		i = rand()%16;
	}
	cc_cards[i] = JAIL;

	// chance cards	
	for(i=0; i<16; i++){
		ch_cards[i] = -1;
	}

	i = rand()%16; ch_cards[i] = GO;
	i = rand()%16; while(ch_cards[i]!=-1){i = rand()%16;} ch_cards[i] = JAIL;
	i = rand()%16; while(ch_cards[i]!=-1){i = rand()%16;} ch_cards[i] = C1;
	i = rand()%16; while(ch_cards[i]!=-1){i = rand()%16;} ch_cards[i] = E3;
	i = rand()%16; while(ch_cards[i]!=-1){i = rand()%16;} ch_cards[i] = H2;
	i = rand()%16; while(ch_cards[i]!=-1){i = rand()%16;} ch_cards[i] = R1;
	i = rand()%16; while(ch_cards[i]!=-1){i = rand()%16;} ch_cards[i] = NR;
	i = rand()%16; while(ch_cards[i]!=-1){i = rand()%16;} ch_cards[i] = NR;
	i = rand()%16; while(ch_cards[i]!=-1){i = rand()%16;} ch_cards[i] = NU;
	i = rand()%16; while(ch_cards[i]!=-1){i = rand()%16;} ch_cards[i] = BACK3;

	cc_pos = rand()%16;
	ch_pos = rand()%16;
}

void roll(){
	int a,b,c,d;

	// printf("%s ",sq_names[curr]);

	// roll dice
	a = rand()%4 + 1;
	b = rand()%4 + 1;

	// printf("(%d %d) ",a,b);

	// jail roll rule
	if(a==b){
		// printf("! ");
		cons_doub++;
	}else{
		cons_doub=0;
	}

	if(cons_doub>=3){
		cons_doub=0;
		curr = JAIL;
		hist[JAIL]++;
		step++;
		// printf("3 doubles JAIL!\n");
		return;
	}

	// next square
	c = (a+b+curr)%40;

	// go to jail
	if(c==G2J){
		c = JAIL;
	}

	// community chest
	if(c==CC1 || c==CC2 || c==CC3){
		d = cc_cards[cc_pos];
		cc_pos = (cc_pos+1)%16;
		if(d!=-1){
			c = d;
		}
	}

	// chance
	if(c==CH1 || c==CH2 || c==CH3){
		d = ch_cards[ch_pos];
		ch_pos = (ch_pos+1)%16;
		if(d==NR){
			switch(c){
				case CH1: c = R2; break;
				case CH2: c = R3; break;
				case CH3: c = R1; break;
				default: break;
			}
		}else if(d==NU){
			switch(c){
				case CH1: c = U1; break;
				case CH2: c = U2; break;
				case CH3: c = U1; break;
				default: break;
			}
		}else if(d==BACK3){
			c = (c-3)%40;
		}else if(d!=-1){
			c = d;
		}

		if(c==CC3){
			d = cc_cards[cc_pos];
			cc_pos = (cc_pos+1)%16;
			if(d!=-1){
				c = d;
			}
		}
	}

	curr = c;
	hist[c]++;
	step++;
	// printf("\n");
	return;
}

void max3(){
	int a,b,c,i;
	a=0; b=0; c=0;

	for(i=0; i<40; i++){
		if(hist[i]>hist[a]){
			c = b;
			b = a;
			a = i;
		}else if(hist[i]>hist[b]){
			c = b;
			b = i;
		}else if(hist[i]>hist[c]){
			c = i;
		}
	}
	printf("%02d%02d%02d\n",a,b,c);
}

void main(){
	int i;
	init();
	for(i=0; i<20000; i++){
		roll();
		if(i%50==49){
			max3();
		}
	}
}