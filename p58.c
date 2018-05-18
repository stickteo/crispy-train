// p58.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define N 14000

void primeseive(int n, bool *b){
	int i, j;
	b[0] = false;
	b[1] = false;

	for(i=2; i<n; i++)
		b[i] = true;

	for(i=2; i<n; i++){
		if(!b[i])
			continue;

		j = i*2;
		while(j<n){
			b[j] = false;
			j += i;
		}
	}
}

int spiral(int n, bool *b){
	int i, j, k, s, t, p;
	s=0; t=1; k=1; j=2;
	for(i=0; i<n; i++){
		k+=j;
		if(b[k])
			s++;
		k+=j;
		if(b[k])
			s++;
		k+=j;
		if(b[k])
			s++;
		k+=j;
		if(b[k])
			s++;
		j+=2;
		t+=4;

		p = 100*s/t;
		//printf("%d: %d / %d = %d\n",i*2+3,s,t,100*s/t);
		if(p<10){
			printf("%d: %d / %d = %d\n",i*2+3,s,t,100*s/t);
			return s;
		}
	}
	return s;
}

void main(){
	bool *prime;
	int s;
	s = (N*2+1)*(N*2+1)+1;
	prime = malloc(s*sizeof(bool));
	primeseive(s,prime);
	printf("%d\n",spiral(N,prime));
}
