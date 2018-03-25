// p92.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define N 10000000

int sdc[N];
bool to1[N];
bool to89[N];

void initSDC(){
	sdc[0] = 0;
	sdc[1] = 1;
	sdc[2] = 4;
	sdc[3] = 9;
	sdc[4] = 16;
	sdc[5] = 25;
	sdc[6] = 36;
	sdc[7] = 49;
	sdc[8] = 64;
	sdc[9] = 81;
}

void calcSDC(){
	int i,s,t,p;
	for(i=10; i<N; i++){
		s = i%10;
		t = i/10;
		p = sdc[t]+sdc[s];
		sdc[i] = p;
	}
}

void initTo189(){
	int i;
	for(i=0; i<N; i++){
		to1[i] = false;
		to89[i] = false;
	}
	to1[1] = true;
	to89[89] = true;
}

bool followChain(int i){
	if(to1[i])
		return false;
	if(to89[i])
		return true;

	bool result;
	result = followChain(sdc[i]);
	if(result){
		to89[i] = true;
	} else {
		to1[i] = true;
	}
	return result;
}

int calcTo189(){
	int i,s;
	s = 0;
	for(i=1; i<N; i++){
		if(followChain(i))
			s++;
	}
	return s;
}

void main(){
	int out;
	initSDC();
	calcSDC();
	initTo189();
	out = calcTo189();

	printf("%d\n",out);
	/*
	int i;
	for(i=0; i<N; i++){
		printf("%d ",sdc[i]);
	}
	*/
	printf("\n");
}