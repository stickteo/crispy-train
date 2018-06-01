// p72.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define L 1000001

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

int *calc_totient(int n, bool *p, int *l){
	int i,j,k,r,s,u;
	int *t;
	bool *b;

	t = malloc(sizeof(int)*n);
	t[0] = 0;
	t[1] = 1;
	for(i=2; i<n; i++){
		t[i] = 0;
	}

	b = malloc(sizeof(bool)*(l[0]+1));
	for(i=2; i<n; i++){
		if(t[i]!=0){
			continue;
		} else if (p[i]) {
			t[i] = i-1;

			if(i>1000)
				continue;

			for(j=i*i; j<n; j*=i){
				t[j] = j*(i-1)/i;
			}
		} else {
			// find 2 coprime numbers
			r=i; k=1; j=l[k]; s=1;
			while(k<=l[0]){
				while(r%j==0){
					s *= j;
					r /= j;
				}
				if(r==i){
					k++;
					j = l[k];
				} else {
					break;
				}
			}
			//printf("%d = %d * %d\n",i,r,s);

			t[i] = t[r] * t[s];

			if(i>1000)
				continue;

			for(j=i*i; j<n; j*=i){
				t[j] = j*t[i]/i;
			}
		}
	}

	return t;
}

void main(){
	bool sieve[L];
	bool *pdiv;
	int *primes;
	int *totients;
	int i,j,k;
	long sum;

	psieve(sieve,L);
	primes = plist(sieve,L);

	pdiv = malloc(sizeof(bool)*(primes[0]+1));
	totients = calc_totient(L, sieve, primes);

	sum = 0;
	for(i=2; i<L; i++){
		//printf("%d %d\n",i,totients[i]);
		sum += totients[i];
	}
	printf("%ld\n", sum);
}