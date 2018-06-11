// p87.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define N 12001

int k_min[N];

void init(){
	int i;
	for(i=0; i<N; i++){
		k_min[i] = INT_MAX;
	}
}

int product_sum(int n, int p, int s, int k, int m){
	int n2, p2, s2, k2, r;
	k2 = p - s + k;

	if(k2<m){
		if(p < k_min[k2]){
			//printf("(%d,%d) ",k2,p);
			k_min[k2] = p;
		}

		r=1;
		n2=n;
		while(r){
			p2 = p*n2;
			s2 = s+n2;
			r = product_sum(n2,p2,s2,k+1,m);
			n2++;
		}
	}else{
		return 0;
	}
	return 1;
}

int unique_sum(){
	int i,j,k;
	int sum;
	bool b[N];

	for(i=2; i<N; i++){
		b[i] = true;
	}

	sum=0;
	for(i=2; i<N; i++){
		if(!b[i]){
			continue;
		}
		k = k_min[i];
		// printf("(%d %d) ",i,k);
		sum += k;
		for(j=i+1; j<N; j++){
			if(k_min[j]==k){
				b[j] = false;
			}
		}
	}

	printf("%d\n",sum);
	return sum;
}

void main(){
	int n, r;

	init();

	n=2;
	while(n<=N){
		product_sum(n,n,n,1,N);
		n++;
	}

	// printf("\n");
	// int i;
	// for(i=2; i<N; i++){
	// 	printf("(%d,%d) ",i,k_min[i]);
	// }
	// printf("\n");

	unique_sum();
}
