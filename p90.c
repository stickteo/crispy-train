// p89.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define M 210

bool comb[M][10];
int nums[9][2] = {{0,1},{0,4},{0,9},{1,6},{2,5},{3,6},{4,9},{6,4},{8,1}};


void init(){
	int i,j;
	for(i=0; i<M; i++){
		for(j=0; j<10; j++){
			comb[i][j]=false;
		}
	}
}

void set(){
	int a,b,c,d,e,f;
	int i;

	i=0;
	for(a=0; a<10; a++){
		for(b=a+1; b<10; b++){
			for(c=b+1; c<10; c++){
				for(d=c+1; d<10; d++){
					for(e=d+1; e<10; e++){
						for(f=e+1; f<10; f++){
							//printf("(%d %d %d %d %d %d)\n",a,b,c,d,e,f);
							comb[i][a]=true; comb[i][b]=true; comb[i][c]=true;
							comb[i][d]=true; comb[i][e]=true; comb[i][f]=true;
							i++;
						}
					}
				}
			}
		}
	}
	printf("%d\n",i);
}

bool check(int i, int j){
	int p,q;
	int k;
	bool b;
	for(k=0; k<9; k++){
		p = nums[k][0];
		q = nums[k][1];

		b = (comb[i][p] && comb[j][q]) || (comb[i][q] && comb[j][p]);
		
		if(p==6 || p==9){
			b = b ||
			    (comb[i][6] && comb[j][q]) || (comb[i][q] && comb[j][6]) ||
			    (comb[i][9] && comb[j][q]) || (comb[i][q] && comb[j][9]);
		}
		if(q==6 || q==9){
			b = b ||
				(comb[i][p] && comb[j][6]) || (comb[i][6] && comb[j][p]) ||
				(comb[i][p] && comb[j][9]) || (comb[i][9] && comb[j][p]);
		}

		if(!b){
			return false;
		}
	}
	return true;
}

void printcomb(int n){
	int i;
	bool f;
	f=true;
	printf("(");
	for(i=0; i<10; i++){
		if(comb[n][i]){
			if(f){
				printf("%d",i);
				f=false;
			}else{
				printf(",%d",i);
			}
		}
	}
	printf(") ");
}

void main(){
	int i,j,k;

	init();
	set();

	k=0;
	for(i=0; i<M; i++){
		for(j=i; j<M; j++){
			if(check(i,j)){
				printcomb(i);
				printcomb(j);
				k++;
				printf("\n");
			}
		}
	}
	printf("%d\n",k);
}
