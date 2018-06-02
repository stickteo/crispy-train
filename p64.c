// p62.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define N 10001

struct list {
	int a;
	int b;
	struct list *next;
};

void addElement(struct list *l, struct list *new){
	struct list *m;
	m = l;
	while(m->next){
		m = m->next;
	}
	m->next = new;
}

bool cmp_add_element(struct list *l, struct list *new){
	struct list *m, *n;
	m = l;
	while(m->next){
		m = m->next;
		if((new->a == m->a) && (new->b == m->b))
			return true;
	}
	m->next = new;
	return false;
}

int frac(int *s, int *d){
	int a, b, c, e;
	c = s[2] - s[1]*s[1];
	a = c/s[0];
	e = (s[1]+s[3])/a;
	b = e*a - s[1];
	d[0] = a;
	d[1] = b;
	d[2] = s[2];
	d[3] = s[3];
	return e;
}

void main(){
	int i, j, k;
	int *s, *d;
	int *z;
	int n, m, nn, mm;
	bool b;
	struct list *h, *e;
	s = malloc(sizeof(int)*4);
	d = malloc(sizeof(int)*4);

	n=1; nn=n*n; m=2; mm=m*m; k=0;
	for(i=2; i<N; i++){
		if(i>=mm){
			n=m; nn=mm;
			m++; mm=m*m;
			continue;
		}
		printf("sqrt(%d) = [%d;(",i,n);
		s[0]=1; s[1]=n; s[2]=i; s[3]=n;
		b = false;
		h = malloc(sizeof(struct list));
		h->next = NULL;
		j=0;
		while(!b){
			e = malloc(sizeof(struct list));
			e->a = s[0]; e->b = s[1];
			e->next = NULL;
			b = cmp_add_element(h,e);
			j++;
			if(!b)
				printf("%d,",frac(s,d));
			z=s; s=d; d=z;
		}
		printf(")] %d\n",j);
		if(j%2==0){
			k++;
		}
	}
	printf("%d\n",k);

/*
	s[0] = 1;
	s[1] = 4;
	s[2] = 23;
	s[3] = 4;
	for(i=0; i<10; i++){
		printf("%d/(sqrt(%d)-%d) = ",s[0],s[2],s[1]);
		printf("%d + ",frac(s,d));
		printf("(sqrt(%d)-%d)/%d\n",d[2],d[1],d[0]);
		z=s; s=d; d=z;
	}
	*/
}

