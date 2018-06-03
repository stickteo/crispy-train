// p74.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define N 1000000
#define M 2177281

int fact[10] = {1,1,2,6,24,120,720,5040,40320,362880};
int term[M];

void init(){
	int i;
	for(i=0; i<M; i++){
		term[i] = 0;
	}
	term[0]=2;
	term[1]=1;
	term[2]=1;

	term[145]=1;

	term[169]=3;
	term[363601]=3;
	term[1454]=3;

	term[871]=2;
	term[45361]=2;

	term[872]=2;
	term[45352]=2;
}

int calc(int n){
	static char s[10];
	int i, j, k, r;
	sprintf(s,"%d",n);
	i=0; r=0;
	while(s[i]){
		j=s[i]-'0';
		r+=fact[j];
		i++;
	}
	return r;
}

int look(int n){
	if(term[n])
		return term[n];
	else{
		int i;
		i = calc(n);
		if(i==n){
			//printf("%d\n", n);
			term[n] = 1;
		} else {
			term[n] = 1 + look(i);	
		}
		return term[n];	
	}
}

void main(){
	init();
	//printf("%d %d\n",363601,calc(363601));
	int i, j, k;
	i=3; k=0;
	while(i<N){
		j=look(i);
		//printf("%d %d\n",i,j);
		if(j==60){
			//printf("*%d %d\n",i,j);
			k++;
		}
		i++;
	}
	printf("%d\n", k);
}
