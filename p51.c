// p51.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define N 1000000

struct list {
	int n;
	struct list *next;
};

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

int nextPrime(int n, bool *b){
	int m;
	m = n + 1;
	while(!b[m]){
		m++;
	}
	return m;
}

int digitMask(int n, int m){
	int a, b, c;
	a = n/10;
	b = 10;
	c = 0;
	while(a>0){
		if(a%10 == m){
			c+=b;
		}
		a/=10;
		b*=10;
	}
	return c;
}

int replaceDigits(int n, bool *b){
	int a,c,d,i,j;
	a = digitMask(n,0);
	if(a){
		d = 0;
		c = n;
		for(i=0; i<10; i++){
			if(b[c]){
				printf("%d ",c);
				d++;
			}
			c += a;
		}
		printf("[%d]\n",d);
		if(d>7)
			return d;
	}

	a = digitMask(n,1);
	if(a){
		d = 0;
		c = n;
		for(i=0; i<9; i++){
			if(b[c]){
				printf("%d ",c);
				d++;
			}
			c += a;
		}
		printf("[%d]\n",d);
		if(d>7)
			return d;
	}

	a = digitMask(n,2);
	if(a){
		d = 0;
		c = n;
		for(i=0; i<8; i++){
			if(b[c]){
				printf("%d ",c);
				d++;
			}
			c += a;
		}
		printf("[%d]\n",d);
		if(d>7)
			return d;
	}

	return 0;
}

void main(){
	int n,d;
	bool *prime = malloc(N*sizeof(bool));
	primeseive(N,prime);

	n = 56003;
	d = 0;
	while(d<8){
		d = replaceDigits(n,prime);
		n = nextPrime(n,prime);		
	}
}
