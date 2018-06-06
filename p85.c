// p85.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define N 2000000
#define M 2001

int t[M];

void init(){
	int i,j,k,l;
	i=0; j=1; k=1;
	for(l=0; l<M; l++){
		t[l] = i;
		//printf("%d ",i);
		i+=j;
		j+=k;
	}
}

// searches ordered array for value n, returns index of
// corresponding value. if no exact match, returns index
// of value just less than n
int search(int n, int s, int *a){
	int i;
	i=0;
	while(i<s && a[i]<n){
		i++;
	}
	return i-1;
}

/*
int search(int n, int s, int *a){
	int i;
	if(s<=0){
		return -1;
	}
	if(s<2){
		return 0;
		if(n < a[0]){
			return -1;
		}else if(n > a[0]){
			return 1;
		}else{
			return 0;
		}
	}
	if(n < a[s/2]){       // search bottom half
		return search(n, s/2, a);
	}else if(n > a[s/2]){ // seach top half
		return s/2 + search(n, (s-1)/2, &a[i+1]);
	}else{
		return s/2;
	}
}
*/

void main(){
	int i,j,k,l,m,n;
	
	init();

	n = N;
	for(i=1; i<M; i++){
		j = N/t[i];
		k = search(j, M, t);
		
		l = t[i] * t[k];
		m = (l > N) ? (l - N) : (N - l);
		if(m<n){
			printf("%d %d %d %d %d\n",i,k,i*k,l,m);
			n = m;
		}

		l = t[i] * t[k+1];
		m = (l > N) ? (l - N) : (N - l);
		if(m<n){
			printf("%d %d %d %d %d\n",i,k+1,i*(k+1),l,m);
			n = m;
		}
	}
}

