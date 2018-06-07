// p75.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define L 1500000
#define M 1225

int len[L];
int s[M];

void init(){
	int i,j,k,l;

	for(i=0; i<L; i++){
		len[i]=0;
	}

	i=0; j=1; k=2;
	for(l=0; l<M; l++){
		s[l]=i;
		i+=j;
		j+=k;
	}
}

int gcd(int a, int b){
	if(b==0){
		return a;
	}else{
		return gcd(b, a%b);
	}
}

void pyth(){
	int a,b,c,d,k,l,m,n;

	for(m=2; m<M; m++){
		int m2 = m*2;
		b = 0;
		for(n=1; n<m; n++){
			b += m2; // b = 2*m*n
			if((m&1) && (n&1)) // both odd
				continue;
			if(gcd(m,n)!=1) // not coprime
				continue;
			a = s[m] - s[n];
			c = s[m] + s[n];
			d = a+b+c;

			if(d<L){
				//printf("[%d %d %d] ",a,b,c);
				l=d;
				while(l<L){
					//printf("%d ",l);
					len[l]++;
					l+=d;
				}
				//printf("\n");
			}else{
				break;
			}
		}
	}
}

void count(){
	int i, j;
	j=0;
	for(i=0; i<L; i++){
		if(len[i]==1)
			j++;
	}
	printf("%d\n", j);
}

void main(){
	init();
	pyth();
	count();
}

