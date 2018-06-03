// p76.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

int part[101][101];

void init(){
	int i, j;
	for(i=0; i<101; i++){
		for(j=0; j<101; j++){
			part[i][j] = 0;
		}
	}
	part[0][0]=1;
	part[1][0]=1;
	part[1][1]=1;
}

int recu(int n, int m){
	if(part[n][m]){
		return part[n][m];
	}else{
		int a,b,c,d;
		b=m; c=n-m; d=1;
		while(c>=b){
			d += recu(c,b);
			b++; c--;
		}
		part[n][m] = d;
		return d;
	}
}

void main(){
	init();
	printf("%d\n",recu(100,1)-1);
}
