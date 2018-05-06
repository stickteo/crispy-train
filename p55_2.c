// p55.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define N 10000
#define ITER 50

char o[64];
char p[64];
char q[64];

void reverse(char *src, char *des){
	int i, e;
	e=0;
	while(src[e]!=0)
		e++;

	des[e] = 0;
	e--;
	for(i=0; i<=e; i++)
		des[i] = src[e-i];
}

void add(char *a, char *b, char *z){
	int i, s, c;
	i=0; c=0;
	while(a[i] && b[i]){
		s = a[i] + b[i] + c - '0' - '0';
		c = s/10;
		z[i] = (s%10) + '0';
		i++;
	}
	while(a[i]){
		s = a[i] + c - '0';
		c = s/10;
		z[i] = (s%10) + '0';
		i++;
	}
	while(b[i]){
		s = b[i] + c - '0';
		c = s/10;
		z[i] = (s%10) + '0';
		i++;
	}
	if(c){
		z[i] = c + '0';
		i++;
	}
	z[i] = 0;
}

bool lychrel(int m){
	bool b;
	int n;
	sprintf(o, "%d", m);
	//printf("%s ",o);
	reverse(o, p);
	add(o, p, q);

	b = true; n = 0;
	while(b && n<50){
		reverse(q, p);
		//printf("%s ",p);
		if(!strcmp(q, p)){
			//printf("\nnot lychrel\n");
			return false;
		}
		add(q, p, q);
		n++;
	}
	return true;
}

void main(){
	int n, s;
	s=0;
	for(n=0; n<10000; n++){
		if(lychrel(n)){
			printf("%d ",n);
			s++;
		}
	}
	printf("\n%d\n",s);
}
