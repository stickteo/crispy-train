// p78.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define N 100000
#define D 1000000

int piles[N];
int penta[N];
int addsub[4] = {1,1,-1,-1};

void initPiles(){
	piles[0] = 1;
	piles[1] = 1;
	piles[2] = 2;
	piles[3] = 3;
	int i;
	for(i=4; i<N; i++){
		piles[i] = -1;
	}
}

void initPenta(){
	int i;
	for(i=1; i<N/2; i++){
		penta[i*2-2] = i*(3*i-1)/2; 
	}
	for(i=1; i<N/2; i++){
		penta[i*2-1] = i*(3*i+1)/2; 
	}
}

/*
int calcPile(int n){
	if(n<=0)
		return 0;
	if(piles[n]>=0)
		return piles[n];

	int a,b,sum;
	sum = 0;
	for(a=1; a<=n/2; a++){
		b = n-a;
		sum += calcPile(b/a);
		if(sum>D*10)
			sum %= D;
	}
	sum = (sum + 1)%D;
	piles[n] = sum;
	return sum;
}
*/

int calcPile(int n){
	int i,j,k,p;
	p = 0;
	for(i=0; i<N; i++){
		j = penta[i];
		if(j>n)
			break;
		k = piles[n-j]*addsub[i%4];
		p = (p+k)%D;
	}
	piles[n] = p%D;
	return piles[n];
}

void main(){
	int i,n;
	initPiles();
	initPenta();
	i = 3;
	n = piles[3];
	while(i<N-1 && n!=0){
		i++;
		n = calcPile(i);
	}
	printf("%d %d\n",i,n);
	
	/*
	for(i=1; i<N; i++){
		printf("%d ",piles[i]);
	}
	*/
	
	printf("\n");
}