// p82.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define N 80

int mat[N][N];
int cst[N][N];

/*
int mat[N][N] = {
	{131,673,234,103, 18},
	{201, 96,342,965,150},
	{630,803,746,422,111},
	{537,699,497,121,956},
	{805,732,524, 37,331}
};
*/

void parse(FILE *f){
	int c, n, i;
	n = 0; i = 0;
	do {
		c = fgetc(f);
		if(c==',' || c=='\n'){
			mat[i/N][i%N] = n;
			n = 0;
			i++;
			continue;
		}
		n = n*10 + c - '0';
	} while(c != EOF);
}

void calcCost(){
	int i, j, k;
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			cst[i][j] = INT_MAX;
		}
	}
	for(i=0; i<N; i++){
		cst[i][0] = mat[i][0];
	}
	for(i=1; i<N; i++){
		int a = cst[j][i-1];
		for(j=0; j<N; j++){
			int a, b;
			a = cst[j][i-1];
			for(k=j; k<N; k++){
				a += mat[k][i];
				if(cst[k][i] > a){
					cst[k][i] = a;
					//printf("cst[%d][%d] = %d\n",k,i,a);
				}
			}
			a = cst[j][i-1];
			for(k=j; k>=0; k--){
				a += mat[k][i];
				if(cst[k][i] > a){
					cst[k][i] = a;
					//printf("cst[%d][%d] = %d\n",k,i,a);
				}
			}
		}
	}

}

void main(){
	FILE *f = fopen("p082_matrix.txt","r");
	parse(f);
	fclose(f);
	calcCost();
	int min, i;
	min = INT_MAX;
	for(i=0; i<N; i++){
		if(cst[i][N-1] < min){
			min = cst[i][N-1];
		}
	}
	printf("%d\n",min);
}
