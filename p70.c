// p70.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define N 10000000
#define NH 3162

bool sv[N];
int *pl;
int ps;

int phi[N];

int num;
long min;

int prime_sieve(bool *b, int n){
	int i,j,k;
	b[0] = false;
	b[1] = false;
	for(i=2; i<n; i++){
		b[i] = true;
	}
	k=0;
	for(i=2; i<n; i++){
		if(!b[i])
			continue;
		
		for(j=i+i; j<n; j+=i){
			b[j] = false;
		}
		k++;
	}
	printf("prime_sieve done\n");
	return k;
}

void bool_to_list(bool *b, int n, int *l){
	int i,j;

	j=0;
	for(i=0; i<n; i++){
		if(b[i]){
			l[j]=i;
			j++;
		}
	}
	printf("done\n");
}

void totient(){
	int i,j,k,l,m,n;

	// init
	for(i=0; i<N; i++){
		phi[i] = 0;
	}
	phi[1] = 1;

	// primes: phi(p) = p-1
	for(i=0; i<ps; i++){
		j=pl[i];
		phi[j] = j-1;

		if(j>NH)
			continue;

		// powers of primes
		// phi(p^n) = (p-1)/p * p^n = (p-1)*p^(n-1)
		k=j*j;
		l=j;
		while(k<N && k>0){
			phi[k] = phi[j] * l;
			l = k;
			k *= j;
		}
	}

	// the rest
	for(i=4; i<N; i++){
		if(phi[i])
			continue;

		// create coprime pair
		// phi(p*q) = phi(p) * phi(q)
		for(j=0; j<ps; j++){
			k = pl[j];
			if(i%k==0){
				break;
			}
		}

		l=i/k;
		m=k;
		while(l%k==0){
			l = l/k;
			m = m*k;
		}

		phi[i] = phi[l] * phi[m];
	}
}

bool sameperm(int a, int b){
	int i;
	char s[11], t[11];
	int u[10], v[10];

	sprintf(s,"%d",a);
	sprintf(t,"%d",b);

	for(i=0; i<10; i++){
		u[i] = 0;
		v[i] = 0;
	}

	i=0;
	while(s[i]){
		u[s[i]-'0']++;
		i++;
	}

	i=0;
	while(t[i]){
		v[t[i]-'0']++;
		i++;
	}

	for(i=0; i<10; i++){
		if(u[i] != v[i]){
			return false;
		}
	}
	return true;
}

void digperm(){
	int i,j;

	long k;

	min = LONG_MAX;

	for(i=2; i<N; i++){
		j = phi[i];
		if(sameperm(i,j)){
			k = (long) N*i/j;
			if(k<min){
				num = i;
				min = k;
				// printf("%d %d\n",i,j);
			}
		}
	}

	printf("%d\n",num);
}

void main(){
	int i,j,k;
	ps = prime_sieve(sv,N);
	pl = malloc(sizeof(int)*ps);
	bool_to_list(sv,N,pl);
	totient();
	digperm();

	// for(i=2; i<100; i++){
	// 	printf("%d: %d\n",i,phi[i]);
	// }
}