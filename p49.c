// p49.c
// https://projecteuler.net/problem=49

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_PRIME 10000
char seive[(MAX_PRIME+7)/8];

void initPrimes(){
	for(int i=0; i<=MAX_PRIME/8; i++)
		seive[i] = 255;
	seive[0] = 252;
	for(int n=2; n<MAX_PRIME; n++){
		bool check = seive[n>>3] & (1 << (n & 7));

		if(!check)
			continue;

		for(int m=n<<1; m<MAX_PRIME; m+=n)
			seive[m>>3] = seive[m>>3] & ~(1 << (m & 7));
	}
}

bool isPrime(int n){
	return seive[n>>3] & (1 << (n & 7));
}

int uniqueSeq(int n){
	int m[4];
	int i, j, p, ans;
	p = n;
	for(i=0; i<4; i++){
		m[i] = p%10;
		p /= 10;
	}
	for(i=0; i<4; i++){
		int max = m[i];
		int k = i;
		for(j=i+1; j<4; j++){
			if(m[j]>max){
				max = m[j];
				k = j;
			}
		}
		if(k!=i){
			m[k] = m[i];
			m[i] = max;
		}
	}
	ans = 0;
	for(i=0; i<4; i++){
		ans *= 10;
		ans += m[i];
	}
	return ans;
}

int main(){
	int size, n, i, j;
	int *primes, *ids;
	initPrimes();
	
	size=0;
	for(n=1000; n<10000; n++){
		if(!isPrime(n))
			continue;
		size++;
		//printf("%d, ",n);
	}
	
	primes = malloc(size * sizeof(int));
	i=0;
	for(n=1000; n<10000; n++){
		if(!isPrime(n))
			continue;
		primes[i] = n;
		i++;
	}

	ids = malloc(size * sizeof(int));

	for(i=0; i<size; i++){
		ids[i] = uniqueSeq(primes[i]);
	}

	for(i=0; i<size; i++){
		for(j=i+1; j<size; j++){
			int next;
			if(ids[i]!=ids[j])
				continue;
			next = (primes[j]<<1)-primes[i];
			if(!isPrime(next))
				continue;
			if(ids[i]==uniqueSeq(next))
				printf("%d %d %d\n",primes[i],primes[j],next);
		}
	}

}