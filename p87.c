// p87.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define N 50000000
#define N2 7072
#define N3 369
#define N4 85

bool sv[N2];
int *pl, *pow2, *pow3, *pow4;
int ps2, ps3, ps4;

bool ss[N];

void init(){
	int i,j,k;

	for(i=0; i<N; i++){
		ss[i] = false;
	}

	for(i=0; i<N2; i++){
		sv[i] = true;
	}
	sv[0] = false;
	sv[1] = false;

	ps2=0; ps3=0; ps4=0;
	for(i=2; i<N2; i++){
		if(!sv[i])
			continue;
		ps2++;
		if(i<N3)
			ps3++;
		if(i<N4)
			ps4++;
		for(j=i+i; j<N2; j+=i){
			sv[j] = false;
		}
	}

	pl = malloc(sizeof(int)*ps2);
	pow2 = malloc(sizeof(int)*ps2);
	pow3 = malloc(sizeof(int)*ps3);
	pow4 = malloc(sizeof(int)*ps4);

	j=0;
	for(i=0; i<N2; i++){
		if(sv[i]){
			pl[j] = i;
			j++;
		}
	}

	for(i=0; i<ps4; i++){
		j = pl[i];
		pow2[i] = j*j;
		pow3[i] = pow2[i]*j;
		pow4[i] = pow3[i]*j;
	}

	for(i=ps4; i<ps3; i++){
		j = pl[i];
		pow2[i] = j*j;
		pow3[i] = pow2[i]*j;
	}

	for(i=ps3; i<ps2; i++){
		j = pl[i];
		pow2[i] = j*j;
	}

	printf("done\n");
}

void calc(){
	int i,j,k;
	int l2, l3, l4, sum;

	for(i=0; i<ps2; i++){
		l2 = pow2[i];
		if(l2>=N)
			break;
		for(j=0; j<ps3; j++){
			l3 = l2 + pow3[j];
			if(l3>=N)
				break;
			for(k=0; k<ps4; k++){
				l4 = l3 + pow4[k];
				if(l4>=N)
					break;
				ss[l4] = true;
			}
			// if(i<2)
			// printf("(%d^2 %d^3 %d^4) (%d %d %d) %d\n",pl[i],pl[j],pl[k],pow2[i],pow3[j],pow4[k],k);
		}
	}

	sum=0;
	for(i=0; i<N; i++){
		if(ss[i])
			sum++;
	}
	printf("%d\n",sum);
}

void main(){
	init();
	calc();
}
