// p100.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define D 1000000000000L

long gcd(long a, long b){
	if(b==0)
		return a;
	else
		return gcd(b, a%b);
}

// void main(){
// 	long i;
// 	long n, d, d2, f1, f2, f3;
// 	long p, q, r, s;
// 	double sqrt2 = sqrt(2.0);

// 	d = D;
// 	for(i=0; i<10000000; i++){
// 		n = (long) round((double) d / sqrt2);

// 		f2 = gcd(n,d);

// 		if(f2==1){
// 			d+=4;
// 			continue;
// 		}

// 		f1 = gcd(n-1,d-1);
// 		// n/d * (n-1)/(d-1) = 1/2 ?
// 		if(f1!=1){
// 			p = n/f2;
// 			q = d/f2/2;

// 			r = (n-1)/f1;
// 			s = (d-1)/f1;

// 			if(p==s || q==r){
// 				printf("%ld %ld (-) ",n,d);
// 				printf("%ld %ld\n",f2,f1);
// 				printf("[%ld %ld] [%ld %ld]\n",p,q,r,s);
// 				long a, b;
// 				a = p; b = q;
// 				printf("%ld %ld\n",a-b,2*b-a);
// 			}
// 		}

// 		f3 = gcd(n+1,d+1);
// 		// (n+1)/(d+1) * n/d = 1/2 ?
// 		if(f3!=1){
// 			p = n/f2;
// 			q = d/f2/2;

// 			r = (n+1)/f3;
// 			s = (d+1)/f3;

// 			if(p==s || q==r){		
// 				printf("%ld %ld (+) ",n,d);
// 				printf("%ld %ld\n",f2,f3);
// 				printf("[%ld %ld] [%ld %ld]\n",p,q,r,s);
// 				long a, b;
// 				a = p; b = q;
// 				printf("%ld %ld\n",a-b,2*b-a);
// 			}
// 		}

// 		d+=4;
// 	}
// }

void main(){
	long p,q,r,s,u,v,x,y;

	p=7; q=5;
	v=0;
	while(v<D){
		r=p-q;  s=2*q-p;
		u=p*r;  v=2*q*r;
		x=q*s;  y=p*s;
		printf("(%ld %ld) (%ld %ld) (%ld %ld) (%ld %ld)\n",p,q,r,s,u,v,x,y);

		r=p+2*q; s=p+q;
		p=r;     q=s;	
	}
}