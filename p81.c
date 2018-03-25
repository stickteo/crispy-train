// p81.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

int mat[80][80];
int cst[80][80];

void parse(FILE *f){
	int c, n, i;
	n = 0; i = 0;
	do {
		c = fgetc(f);
		if(c==',' || c=='\n'){
			mat[i/80][i%80] = n;
			n = 0;
			i++;
			continue;
		}
		n = n*10 + c - '0';
	} while(c != EOF);
}

/*
void init(){
	int i, j;
	for(i=0; i<80; i++){
		for(j=0; j<80; j++){
			cst[i][j] = INT_MAX;
		}
	}
}
*/

void calcCost(){
	int i, j;
	cst[0][0] = mat[0][0];
	for(i=1; i<80; i++){
		cst[0][i] = cst[0][i-1] + mat[0][i];
	}
	for(i=1; i<80; i++){
		cst[i][0] = cst[i-1][0] + mat[i][0];
	}
	for(i=1; i<80; i++){
		for(j=1; j<80; j++){
			int a, b;
			a = cst[i-1][j];
			b = cst[i][j-1];

			cst[i][j] = mat[i][j] + ((a<b) ? a : b);

			printf("%d ", cst[i][j]);
		}
	}
}

void main(){
	FILE *f = fopen("p081_matrix.txt","r");
	parse(f);
	calcCost();
	printf("%d\n",cst[79][79]);
	fclose(f);
}
