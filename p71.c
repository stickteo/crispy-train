// p71.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define N 3
#define D 7

#define L 1000000

int comp(int n1, int d1, int n2, int d2){
	return n1*d2 - n2*d1;
}

void main(){
	int n, d, n2, d2, n3, d3;
	n = 3; d = 8;
	n2 = n; d2 = d;
	n3 = n; d3 = d;
	while(d2<=L){
		while(comp(n2,d2,N,D)<0){
			n2++;
			//printf(".");
		}
		n2--;
		if(comp(n2,d2,n,d)>0){
			n = n2;
			d = d2;
			//printf("%d %d\n",n,d);
		}
		d2++;
	}
	printf("%d %d\n",n,d);
}
