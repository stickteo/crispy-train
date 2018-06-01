// p69.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define L 1000000

void psieve(bool *b, int n){
	int i, j;
	b[0] = false;
	b[1] = false;
	for(i=2; i<n; i++){
		b[i] = true;
	}
	for(i=2; i<n; i++){
		if(b[i]){
			for(j=i+i; j<n; j+=i){
				b[j] = false;
			}
		}
	}
}

int *plist(bool *b, int n){
	int i, j, *p;

	j=0;
	for(i=2; i<n; i++){
		if(b[i])
			j++;
	}

	p = malloc(sizeof(int)*(j+1));
	p[0] = j;

	j=1;
	for(i=2; i<n; i++){
		if(b[i]){
			p[j] = i;
			j++;
		}
	}
	return p;
}

void totient(int *n, int s){

}

void main(){
	bool sieve[L];
	bool sieve2[L];
	int *primes;
	int i,j,k;

	psieve(sieve,L);
	primes = plist(sieve,L);

	j = primes[0]; k=1;
	for(i=1; i<=j; i++){
		k *= primes[i];
		if(k>L)
			break;
	}
	k = k/primes[i];

	printf("%d\n",k);
}