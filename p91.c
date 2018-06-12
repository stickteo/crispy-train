// p91.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define M 51

int coor[M*M][2];

void init(){
	int i,j,k;

	k=0;
	for(i=0; i<M; i++){
		for(j=0; j<M; j++){
			//printf("(%d %d) ",i,j);
			coor[k][0] = i; // x
			coor[k][1] = j; // y
			k++;
		}
	}
}

bool test_right(int a, int b){
	int ax, ay, bx, by;
	bool c;
	ax = coor[a][0]; ay = coor[a][1];
	bx = coor[b][0]; by = coor[b][1];

	if(ax*by == ay*bx)
		return false;

	c = false;
	c |= (ax*(bx-ax) + ay*(by-ay) == 0);
	c |= (bx*(bx-ax) + by*(by-ay) == 0);
	c |= (ax*bx + ay*by == 0);

	return c;
}

void main(){
	int a,b;
	long ans;
	init();

	ans = 0;
	for(a=0; a<M*M; a++){
		//printf("***(%d,%d)***\n",coor[a][0],coor[a][1]);
		for(b=a+1; b<M*M; b++){
			if(test_right(a,b)){
				//printf("(%d,%d) ",coor[b][0],coor[b][1]);
				ans++;
			}
		}
		//printf("\n");
	}
	printf("%ld\n",ans);
}
