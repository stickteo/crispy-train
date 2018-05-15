// p54.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

/* ranks */
/*
0 = high card
1 = one pair
2 = two pair
3 = three of a kind
4 = straight
5 = flush
6 = full house
7 = four of a kind
8 = straight flush
9 = royal flush
*/

/* value */
/*
up to 5 possible comparisons with high card:
if 1st highest card equal, then compare 2nd highest ...

in order:
 2, 3, 4, 5, 6, 7, 8, 9, T, J,  Q,  K,  A
(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12)

value = 13^5*rank + 13^4*1st + 13^3*2nd + 13^2*3rd + 13*4th + 5th
*/

int pow13[6] = {1,13,169,2197,28561,371293};

struct hand {
	bool cards[4][13];
};

int eval(struct hand *h){
	int r, i, j, k;
	int *l;
	int v[5], c[13], s[4];
	bool b;
	bool *t;

	//royal flush
	for(j=0; j<4; j++){
		t = &(h->cards[j][0]);
		b = t[9] && t[10] && t[11] && t[12] && t[13];
		if(b){
			return pow13[5]*9;
		}
	}

	//straight flush
	for(j=0; j<4; j++){
		for(k=0; k<8; k++){
			t = &(h->cards[j][k]);
			b = t[0] && t[1] && t[2] && t[3] && t[4];
			if(b){
				return pow13[5]*8 + pow13[4]*(k+4);
			}
		}
	}

	//calculate some stats
	for(j=0; j<4; j++){
		t = &(h->cards[j][0]);
		s[j] = t[0]+t[1]+t[2]+t[3]+t[4]+
		       t[5]+t[6]+t[7]+t[8]+t[9]+
		       t[10]+t[11]+t[12];
		//printf("%d ",s[j]);
	}
	//printf("\n");

	for(k=0; k<13; k++){
		t = &(h->cards[0][k]);
		c[k] = t[0] + t[13] + t[26] + t[39];
		//printf("%d ",c[k]);
	}
	//printf("\n");

	//four of a kind
	for(k=0; k<13; k++){
		if(c[k]==4)
			return pow13[5]*7 + pow13[4]*k;
	}

	//full house
	v[0]=-1; v[1]=-1;
	for(k=0; k<13; k++){
		if(c[k]==3)
			v[0] = k;
		if(c[k]==2)
			v[1] = k;
	}
	if(v[0]>=0 && v[1]>=0)
		return pow13[5]*6 + pow13[4]*v[0] + pow13[3]*v[1];

	//flush
	for(j=0; j<4; j++){
		if(s[j]==5){
			i = 4;
			t = &(h->cards[j][0]);
			for(k=0; k<13; k++){
				if(t[k]){
					v[i] = k;
					i--;
				}
			}
			return pow13[5]*5 + pow13[4]*v[0] + pow13[3]*v[1] +
			       pow13[2]*v[2] + pow13[1]*v[3] + pow13[0]*v[4];
		}
	}

	//straight
	for(k=0; k<8; k++){
		l = &c[k];
		b = l[0] && l[1] && l[2] && l[3] && l[4];
		if(b){
			return pow13[5]*4 + pow13[4]*(k+4);
		}
	}

	//three of a kind
	for(k=0; k<13; k++){
		if(c[k]==3)
			return pow13[5]*3 + pow13[4]*k;
	}

	//two pairs
	v[0] = -1; v[1] = -1; i = 1;
	for(k=0; k<13; k++){
		if(c[k]==2){
			v[i] = k;
			i--;
		}
		if(c[k]==1){
			v[2] = k;
		}
	}
	if(v[0]>=0 && v[1]>=0){
		return pow13[5]*2 + pow13[4]*v[0] +
	           pow13[3]*v[1] + pow13[2]*v[2];
	}

	//one pair
	v[0] = -1; i = 3;
	for(k=0; k<13; k++){
		if(c[k]==2){
			v[0] = k;
		}
		if(c[k]==1 && i>0){
			v[i] = k;
			i--;
		}
	}
	if(v[0]>=0){
		return pow13[5]*1 + pow13[4]*v[0] +
	           pow13[3]*v[1] + pow13[2]*v[2] + pow13[1]*v[3];
	}

	//high card
	i = 4;
	for(k=0; k<13; k++){
		if(c[k]){
			v[i] = k;
			i--;
		}
	}
	return pow13[4]*v[0] + pow13[3]*v[1] +
	       pow13[2]*v[2] + pow13[1]*v[3] + pow13[0]*v[4];
}

void clearHand(struct hand *h){
	int j,k;
	for(j=0; j<4; j++){
		for(k=0; k<13; k++){
			h->cards[j][k] = false;
		}
	}
}

void parseHand(char *s, struct hand *h1, struct hand *h2){
	int i;
	int suit, valu;
	clearHand(h1);
	clearHand(h2);
	for(i=0; i<15; i+=3){
		switch(s[i]){
			case 'A': valu = 12; break;
			case 'K': valu = 11; break;
			case 'Q': valu = 10; break;
			case 'J': valu =  9; break;
			case 'T': valu =  8; break;
			default : valu = s[i]-'2'; break;
		}
		switch(s[i+1]){
			case 'H': suit = 0; break;
			case 'D': suit = 1; break;
			case 'C': suit = 2; break;
			default : suit = 3; break;
		}
		h1->cards[suit][valu] = true;
	}
	for(i=15; i<30; i+=3){
		switch(s[i]){
			case 'A': valu = 12; break;
			case 'K': valu = 11; break;
			case 'Q': valu = 10; break;
			case 'J': valu =  9; break;
			case 'T': valu =  8; break;
			default : valu = s[i]-'2'; break;
		}
		switch(s[i+1]){
			case 'H': suit = 0; break;
			case 'D': suit = 1; break;
			case 'C': suit = 2; break;
			default : suit = 3; break;
		}
		h2->cards[suit][valu] = true;
	}
}

void main(){
	FILE *f;
	char b[256];
	struct hand *h1, *h2;
	int p1, p2, n;
	h1 = malloc(sizeof(struct hand));
	h2 = malloc(sizeof(struct hand));
	f = fopen("p054_poker.txt","r");
	b[0] = 0;
	n = 0;
	while(fgets(b,256,f) != NULL){
		parseHand(b,h1,h2);
		p1 = eval(h1);
		p2 = eval(h2);
		printf("%d %d\n",p1,p2);
		if(p1>p2){
			n++;
		}
	}
	printf("%d\n",n);
}
