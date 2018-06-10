// p73.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>

#define D 100000001
#define LO 3
#define HI 2

int count[D];

void main(){
	clock_t start, end;
	float seconds;
	int i,j;
	int lo, hi;
	long ans;

	start = clock();

	for(i=0; i<D; i++){
		count[i] = 0;
	}

	ans=0;
	for(i=2; i<D; i++){
		lo=i/LO+1;
		hi=i/HI;
		
		count[i] += hi-lo+1;
		ans += count[i];
		for(j=i+i; j<D; j+=i){
			count[j] -= count[i];
		}
		//printf("%d %d\n",i,count[i]);
	}

	end = clock();
	seconds = (float)(end - start) / CLOCKS_PER_SEC;
	
	printf("%fs\n", seconds);
	printf("%ld\n",ans-1);
}

