// p27.c
// https://projecteuler.net/problem=27


#include <stdio.h>
#include <stdbool.h>

#define MAX_N 100
#define MAX_PRIME 1000000

int square[MAX_N+1];
char seive[(MAX_PRIME+7)/8];

void initSquareNums(){
	for(int n=0; n<=MAX_N; n++){
		square[n] = n*n;
	}
}

void initPrimes(){
	for(int i=0; i<=MAX_PRIME/8; i++)
		seive[i] = 255;
	seive[0] = 252;
	for(int n=2; n<=MAX_PRIME; n++){
		bool check = seive[n>>3] & (1 << (n & 7));

		if(!check)
			continue;

		for(int m=n<<1; m<=MAX_PRIME; m+=n)
			seive[m>>3] = seive[m>>3] & ~(1 << (m & 7));
	}
}

bool isPrime(int n){
	if(n<0)
		n = n*(-1);
	return seive[n>>3] & (1 << (n & 7));
}

void calculate(){
	int a, b, n, max;
	max = 0;
	for(b=-1000; b<=1000; b++){
		if(!isPrime(b))
			continue;

		for(a=-999; a<=999; a++){
			for(n=0; n<=MAX_N; n++){
				int sum = square[n] + n*a + b;
				if(!isPrime(sum)){
					if(n>=max){
						printf("b=%d, a=%d, n=%d, b*a=%d\n",b,a,n,a*b);
						max = n;
					}
					break;
				}
			}
			if(n>MAX_N)
				printf("increase max n\n");
		}
	}
}

int main(){
	initSquareNums();
	initPrimes();
	calculate();
}
