// p56.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define L 200
#define N 100

int acc[L];
int tmp[L];

void init(int n){
	int i;
	for(i=0; i<L; i++){
		acc[i] = 0;
		tmp[i] = 0;
	}
	acc[0] = n%10;
	acc[1] = (n/10)%10;
}

void mul(int n){
	int i;
	for(i=0; i<L; i++){
		tmp[i] = acc[i] * n;
	}
	for(i=1; i<L; i++){
		tmp[i] += tmp[i-1]/10;
		tmp[i-1] %= 10;
	}
	tmp[L-1] %= 10;
	for(i=0; i<L; i++){
		acc[i] = tmp[i];
		tmp[i] = 0;
	}
}

int sum(){
	int i, s;
	s = 0;
	for(i=0; i<L; i++)
		s += acc[i];
	return s;
}

void calc(){
	int a, b, c, max;
	max = 0;
	for(a=2; a<N; a++){
		init(a);
		for(b=2; b<N; b++){
			mul(a);
			c = sum();
			if(max < c){
				max = c;
				printf("%d^%d = %d\n",a,b,c);
			}
		}
	}
}

void main(){
	calc();
}