// p86.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>

#define M 2001
#define M2 (M*2-1)
#define S 1000000

int squa[M];
bool pyth[M][M2];

void init(){
	int i,j,k;
	int m,n,p,q;
	int a,b,c;

	// init arrays
	for(i=0; i<M; i++){
		squa[i]=0;
	}

	for(i=0; i<M; i++){
		for(j=0; j<M2; j++){
			pyth[i][j]=false;
		}
	}

	// find squares
	i=0; j=1; k=2;
	for(m=0; m<M; m++){
		squa[m] = i;
		//printf("%d ",i);
		i+=j;
		j+=k;
	}

	// find pythagorean triples
	for(m=2; m<M; m++){
		k=m*2; b=0;
		for(n=1; n<m; n++){
			a = squa[m] - squa[n];
			b += k;
			// b = m*n*2;
			if(a>b){
				p=b; q=a;
			}else{
				p=a; q=b;
			}
			//printf("%d %d\n",p,q);
			i=p; j=q;
			while(i<M && j<M2){
				//printf(".");
				pyth[i][j] = true;
				i+=p; j+=q;
			}
		}
	}
}

void calc(){
	int i,j,k;
	int a,b;
	int sum;

	sum=0;
	for(i=1; i<M; i++){
		k=2;
		for(j=2; j<=i*2; j++){
			//printf("%d ",k/2);
			if(i>=j){
				a=j; b=i;
			}else{
				a=i; b=j;
			}
			if(pyth[a][b]){
				sum+=k/2;
			}
			if(i>=j){
				k++;
			}else{
				k--;
			}
		}
		if(sum>S){
			printf("%d %d\n",i,sum);
			break;
		}
		//printf("\n");
	}
	// printf("%d\n",sum);
}

void main(){
	clock_t start, end;
	float seconds;

	init();
	calc();


	end = clock();
	seconds = (float)(end - start) / CLOCKS_PER_SEC;
	printf("%fs\n", seconds);
}

