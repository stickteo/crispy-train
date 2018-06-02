// p57.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define N 100

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
	if(a[i]){
		while(a[i]){
			s = a[i] + c - '0';
			c = s/10;
			z[i] = (s%10) + '0';
			i++;
		}	
	}else if(b[i]){
		while(b[i]){
			s = b[i] + c - '0';
			c = s/10;
			z[i] = (s%10) + '0';
			i++;
		}	
	}
	if(c){
		z[i] = c + '0';
		i++;
	}
	z[i] = 0;
}

void mul(char *a, char *b, char *y, char *z){
	int i, j, m, n, p;
	i=0;
	z[0]='0'; z[1]=0;
	while(a[i]){
		j=0; p=0;
		m = a[i] - '0';
		while(b[j]){
			n = m * (b[j]-'0') + p;
			y[j] = (n%10) + '0';
			p = n/10;
			j++;
		}
		if(p){
			y[j] = p + '0';
			j++;
		}
		y[j]=0;

		add(&y[0],&z[i],&z[i]);
		i++;
	}
}

void main(){
	int i, j, s;
	int p[N];
	char *n, *d, *e, *f, *g, *z;
	n = malloc(512*sizeof(char));
	d = malloc(512*sizeof(char));
	e = malloc(512*sizeof(char));
	f = malloc(512*sizeof(char));
	g = malloc(512*sizeof(char));

	p[0] = 2;
	for(i=1; i<N; i++){
		p[i] = 1;
	}
	j = 2;
	for(i=2; i<N; i+=3){
		p[i] = j;
		j += 2;
	}

	n[0] = '1'; n[1] = 0;
	sprintf(e,"%d",p[N-1]);
	reverse(e,d);

	for(i=N-2; i>=0; i--){
		//printf("%s %s\n",n,d);
		sprintf(g,"%d",p[i]);
		reverse(g,e);
		mul(d,e,f,g);
		add(n,g,n);
		z=n; n=d; d=z;
	}

	s=0; i=0;
	while(d[i]){
		s += d[i] - '0';
		i++;
	}
	printf("%d\n",s);
}
