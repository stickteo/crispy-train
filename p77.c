// p77.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define N 101

int part[N][N];
bool pbool[N];
int *primes;

void psieve(int n, bool *b){
	int i,j;
	for(i=0; i<n; i++){
		b[i]=true;
	}
	b[0]=false;
	b[1]=false;
	for(i=2; i<n; i++){
		if(!b[i])
			continue;
		for(j=i+i; j<n; j+=i){
			b[j]=false;
		}
	}
}

// returns array of int i given b[i]=true
int *btoi(int s, bool *b){
	int i,j;
	int *n;
	j=0;
	for(i=0; i<s; i++){
		if(b[i])
			j++;
	}
	n = malloc(sizeof(int)*(j+1));
	j=0;
	for(i=0; i<s; i++){
		if(b[i]){
			n[j]=i;
			j++;
		}
	}
	n[j]=0;
	return n;
}

void init(){
	int i, j;
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			part[i][j] = 0;
		}
	}
	psieve(N,pbool);
	primes = btoi(N,pbool);
}

int recu(int n, int m){
	if(part[n][m]){
		return part[n][m];
	}else{
		int a,b,c,d;
		a=m; b=primes[a]; c=n-b; d=0;
		
		if(pbool[n])
			d++;
		while(c>=b){
			d += recu(c,a);
			a++; b=primes[a]; c=n-b;
		}
		part[n][m] = d;
		return d;
	}
}

void main(){
	int i;
	init();
	for(i=2; i<N; i++){
		printf("%d %d\n",i, recu(i,0));
	}
}
