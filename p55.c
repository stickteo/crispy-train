// p55.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define N 10000
#define ITER 50

char ab[64];
char bb[64];

bool isLychrel[N];
long chain[ITER];

void init(){
	int i;
	for(i=0; i<N; i++){
		isLychrel[i] = true;
	}
}

void reverse(char *src, char *des){
	int i, e;
	e=0;
	while(src[e]!=0)
		e++;

	des[e] = 0;
	e--;
	for(i=0; i<=e; i++)
		des[i] = src[e-i];
}

bool lychrel(long n, char *a, char *b, long *s){
	long m;
	sprintf(a, "%ld", n);
	reverse(a, b);
	m = atol(b);
	*s = n + m;
	if(*s<0)
		printf("overflow!\n");
	return (n==m);
}

void testLychrel(long n){
	int i, j;
	bool b;

	if(!isLychrel[n])
		return;

	chain[0] = n;
	lychrel(chain[0], ab, bb, &chain[1]);
	
	for(i=2; i<ITER; i++){
		b = false;
		b |= lychrel(chain[i-1], ab, bb, &chain[i]);
		if(chain[i]<N && chain[i]>=0)
			b |= !isLychrel[chain[i]];

		if(b){
			for(j=0; j<i; j++){
				if(chain[j]<N)
					isLychrel[chain[j]] = false;
			}
			return;
		}
	}
}

void main(){
	long i;
	int c;

	init();

	for(i=0; i<N; i++){
		testLychrel(i);
	}

	c = 0;
	for(i=0; i<N; i++){
		if(isLychrel[i]){
			printf("%ld ", i);
			c++;
		}
	}
	printf("\n%d\n",c);
	printf("%ld\n",LONG_MAX);
	printf("%lld\n",LLONG_MAX);
}
