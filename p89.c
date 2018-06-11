// p89.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include <math.h>

int rn_to_int(char *s){
	int i,val;
	
	val=0; i=0;
	while(s[i]){
		switch(s[i]){
			case 'M': val+=1000; break;
			case 'D': val+=500; break;
			case 'C':
				if(s[i+1]=='M' || s[i+1]=='D') {val-=100;}
				else {val+=100;}
				break;
			case 'L': val+=50; break;
			case 'X':
				if(s[i+1]=='C' || s[i+1]=='L') {val-=10;}
				else {val+=10;}
				break;
			case 'V': val+=5; break;
			case 'I':
				if(s[i+1]=='X' || s[i+1]=='V') {val-=1;}
				else {val+=1;}
				break;
			default: break;
		}
		i++;
	}
	return val;
}

// 0 = _ => 0
// 1 = i,x,c => 1
// 2 = ii,xx,cc => 2
// 3 = iii,xxx,ccc => 3
// 4 = iv,xl,cd => 2
// 5 = v,l,d => 1
// 6 = vi,lx,dc => 2
// 7 = vii,lxx,dcc => 3
// 8 = viii,lxxx,dccc => 4
// 9 = ix,xc,cm => 2
int dlen[10] = {0,1,2,3,2,1,2,3,4,2};

int int_to_rnlen(int n){
	int i,j;
	int len;

	len=0;
	i=0; j=n;
	while(j>0){
		if(i>=3){ // thousands place, M
			len+=j;
			break;
		}else{
			len+=dlen[j%10];
		}
		j = j/10;
		i++;
	}
	return len;
}

void main(){
	FILE *f;
	int i,j,k,l;
	int sav;
	char s[100];

	f = fopen("p089_roman.txt","r");
	i=1; sav=0;
	while(fgets(s,100,f)!=NULL){
		j=rn_to_int(s);
		k=(int) strlen(s)-1;
		l=int_to_rnlen(j);
		sav += k-l;
		printf("%4d %4d %2d %2d\n",i,j,k,l);
		i++;
	}
	printf("%d\n",sav+1);
}