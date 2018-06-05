// p80.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAX 0x7FFFFFFFFFFFFFF
#define MAXBIT 59
#define BL 6

struct bignum{
	long n[BL];
};

void ltobig(long n, struct bignum *b){
	//struct bignum *b;
	int i;
	//b = malloc(sizeof(struct bignum));
	for(i=0; i<BL; i++){
		b->n[i]=0;
	}
	b->n[0] = n & MAX;
	//return b;
}

long bigdivl(struct bignum *a, struct bignum *b){
	int i,j;
	long c,d,e,f,g,h;
	struct bignum *y,*z;

	// find divident and divisor
	i=0;
	while(i<BL && a->n[i]){
		i++;
	}
	i--;
	j=0;
	while(j<BL && b->n[j]){
		j++;
	}
	j--;

	// divident too large
	// if(i>j+1 || j>i+1)
	// 	return MAX;

	if(i>j){
		z=a; y=b;
	}else if(i<j){
		z=b; y=a; i=j;
	}else{
		if(a->n[i] > b->n[i]){
			z=a; y=b;
		}else{
			z=b; y=a;
		}
	}

	/*
	while(a->n[i] && b->n[i] && i<BL){
		i++;
	}

	if(i<BL && a->n[i]){
		z=a; y=b;
	} else {
		z=b; y=a;
	}
	*/

	// divident too large
	/*
	if(i+1<BL && z->n[i+1]){
		return 0;
	}
	*/

	// mask off proper bits
	c=1; d=0;
	while(c < z->n[i]){
		c = c<<1;
		d++;
	}
	c--;

	e = ((z->n[i])<<(MAXBIT-d)) + (((z->n[i-1])&(MAX-c))>>d);
	f = ((y->n[i])<<(MAXBIT-d)) + (((y->n[i-1])&(MAX-c))>>d);

	// divide by zero
	if(f==0){
		return -1;
	}

	return e/f;
}

void bigmul10(struct bignum *a, long m, struct bignum *z){
	int i;
	long c, d;

	c=0;
	for(i=0; i<BL; i++){
		d = (a->n[i]*m) + c;
		c = (d & (~MAX))>>MAXBIT;
		z->n[i] = d & MAX;
	}
}

void bigadd(struct bignum *a, struct bignum *b, struct bignum *z){
	int i;
	long c, d;

	c=0;
	for(i=0; i<BL; i++){
		d = a->n[i] + b->n[i] + c;
		c = (d & (~MAX))>>MAXBIT;
		z->n[i] = d & MAX;
	}
}

void bigsub(struct bignum *a, struct bignum *b, struct bignum *z){
	int i;
	long c, d;

	c=0;
	for(i=0; i<BL; i++){
		d = a->n[i];
		
		if(c)
			d--;

		if(d < b->n[i]){
			d += MAX + 1 - b->n[i];
			c=1;
		} else {
			d -= b->n[i];
			c=0;	
		}
		z->n[i] = d & MAX;
	}
}

long bigcmp(struct bignum *a, struct bignum *b){
	int i, j;
	i=0; j=0;
	while(i<BL && a->n[i]){
		i++;
	}
	while(j<BL && b->n[j]){
		j++;
	}
	if(i<j){
		return -1;
	}
	if(i>j){
		return 1;
	}
	i--;
	while(a->n[i] && b->n[i] && i>=0){
		if(a->n[i] > b->n[i]){
			return 1;
		}else if(a->n[i] < b->n[i]){
			return -1;
		}
		i--;
	}
	return 0;
}

void main(){
	long i,j,k,l,m,n,p,q,sum;
	long a,b,c,d;

	struct bignum *r, *s, *t, *u;
	r = malloc(sizeof(struct bignum));
	s = malloc(sizeof(struct bignum));
	t = malloc(sizeof(struct bignum));
	u = malloc(sizeof(struct bignum));
	
	sum = 0;
	a=1; b=3; c=2; d=1;
	for(i=2; i<100; i++){
		if(i>a+b){
			a+=b; b+=c;	d++;
		}
		if(i==a+b){
			continue;
		}
		p=0; q=0;

		j=i-a; k=d*2;
		printf("%ld %ld.",i,d);
		p+=d; q++;

		j*=10;
		l=j/k;
		j*=10; k*=10;
		while((k+l)*l>j){
			l--;
		}
		printf("%ld",l);
		p+=l; q++;

		j = j - (k+l)*l;
		k = k + l*2;

		//printf(" %d %d\n",j,k);
		//continue;

		ltobig(j,r);
		ltobig(k,s);
		for(j=1; j<100; j++){
			bigmul10(r,10,r);
			m = bigdivl(r,s);
			m++;
			bigmul10(r,10,r);
			bigmul10(s,10,s);

			if(m>=10){
				m=9;
			}

			m++;
			do{
				m--;
				ltobig(m*m,t);
				bigmul10(s,m,u);
				bigadd(t,u,t);
				n = bigcmp(t,r);
			} while(n>0 && m>0);

			printf("%ld",m);
			if(q<100){
				p+=m; q++;
			}
			// printf("[%015lx %015lx] ",r->n[0]<<1, r->n[1]);
			bigsub(r,t,r);
			// printf("[%015lx %015lx]\n",t->n[0]<<1, t->n[1]);
			// printf("  [%015lx %015lx]\n",r->n[0]<<1, r->n[1]);
			ltobig(m*2,u);
			bigadd(s,u,s);
		}
		printf(" %ld\n",p);
		sum+=p;
	}
	printf("%ld\n",sum);
}

