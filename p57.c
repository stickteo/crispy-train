// p57.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define N 1000

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

void swap(char *a, char *b){
	char *z;
	z = a;
	a = b;
	b = z;
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

void main(){
	int i, s;
	char *n, *d, *n2, *z;
	n = malloc(512*sizeof(char));
	d = malloc(512*sizeof(char));
	n2 = malloc(512*sizeof(char));

	n[0] = '1'; n[1] = 0;
	d[0] = '2'; d[1] = 0;

	s=0;
	for(i=0; i<N; i++){
		add(n,d,n2);
		if(strlen(n2)>strlen(d)){
			s++;
			printf("* ");
		}
		printf("%s %s\n",n2,d);
		add(n,d,n);
		add(n,d,n);
		z = n;
		n = d;
		d = z;
	}
	printf("%d\n",s);

}
