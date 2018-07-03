// p60.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define N 50000

struct sprime {
	int n;
	bool *b;
	int *pl;
	int ps;
};

void prime_sieve(struct sprime *s){
	int i,j,k;

	for(i=0; i<s->n; i++){
		s->b[i]=true;
	}
	s->b[0]=false;
	s->b[1]=false;
	k=0;
	for(i=2; i<s->n; i++){
		if(!s->b[i])
			continue;
		for(j=i+i; j<s->n; j+=i){
			s->b[j]=false;
		}
		k++;
	}

	s->pl = malloc(sizeof(int)*k);
	s->ps = k;
	j = 0;
	for(i=2; i<s->n; i++){
		if(s->b[i]){
			s->pl[j] = i;
			j++;
		}
	}
}

bool prime_check(struct sprime *s, int m){
	if(m<2){
		return false;
	}else if(m<s->n){
		return s->b[m];
	}else{
		int i,j,k,l;

		// l=(s->n)*(s->n);
		// if(m>l){
		// 	printf("prime: indeterminate\n");
		// 	return false;
		// }

		for(i=0; i<s->ps; i++){
			j=s->pl[i];
			k=m%j;
			l=m/j;

			if(l<j)
				break;
			if(k==0)
				return false;
		}
		return true;
	}
}

int concat(int a, int b){
	char s[20];
	sprintf(s,"%d%d",a,b);
	return atoi(s);
}

int roundpow10(int n){
	if(n<10){
		return 10;
	}else if(n<100){
		return 100;
	}else if(n<1000){
		return 1000;
	}else if(n<10000){
		return 10000;
	}else if(n<100000){
		return 100000;
	}else if(n<1000000){
		return 1000000;
	}else if(n<10000000){
		return 10000000;
	}else if(n<100000000){
		return 100000000;
	}else if(n<1000000000){
		return 1000000000;
	}else{
		return -1;
	}
}

struct sprime *primes;
bool *prop;

void init(){
	int i,j,k;

	primes = malloc(sizeof(struct sprime));
	primes->n = N;
	primes->b = malloc(sizeof(bool)*N);
	prime_sieve(primes);

	prop = malloc(sizeof(bool)*(primes->ps)*(primes->ps));
	for(i=0; i<primes->ps; i++){
		k = i * primes->ps;
		for(j=0; j<primes->ps; j++){
			prop[k+j] = false;
		}
	}
}

int search(int l, int a, int b, int c, int d, int e){
	int i,j,k;
	switch(l){
		case 5:
		i = e*primes->ps;
		if(!prop[i+a] || !prop[i+b] || !prop[i+c] || !prop[i+d])
			return 0;
		printf("!!!!! %d %d %d %d %d !!!!!\n",primes->pl[a],primes->pl[b],primes->pl[c],primes->pl[d],primes->pl[e]);
		return primes->pl[a]+primes->pl[b]+primes->pl[c]+primes->pl[d]+primes->pl[e];

		case 4:
		i = d*primes->ps;
		if(!prop[i+a] || !prop[i+b] || !prop[i+c])
			return 0;

		// printf("%d %d %d %d\n",primes->pl[a],primes->pl[b],primes->pl[c],primes->pl[d]);
		break;

		case 3:
		i = c*primes->ps;
		if(!prop[i+a] || !prop[i+b])
			return 0;
		break;

		case 2:
		i = b*primes->ps;
		if(!prop[i+a])
			return 0;
		break;

		default:
		break;
	}

	switch(l){
		case 4:
		i=d+1;
		k=0;
		while(i<primes->ps && k==0){
			k = search(5,a,b,c,d,i);
			i++;
		}
		return k;

		case 3:
		i=c+1;
		k=0;
		while(i<primes->ps && k==0){
			k = search(4,a,b,c,i,i);
			i++;
		}
		return k;

		case 2:
		i=b+1;
		k=0;
		while(i<primes->ps && k==0){
			k = search(3,a,b,i,i,i);
			i++;
		}
		return k;

		case 1:
		i=a+1;
		k=0;
		while(i<primes->ps && k==0){
			k = search(2,a,i,i,i,i);
			i++;
		}
		return k;

		case 0:
		i=1;
		k=0;
		while(i<primes->ps && k==0){
			k = search(1,i,i,i,i,i);
			i++;
		}
		return k;		

		default:
		return 0;
	}

	return 0;
}

void calc(){
	int i,j,k,l,m,n,p,q;

	for(i=1; i<primes->ps; i++){
		if(i==2)
			continue;

		k = primes->pl[i];
		l = roundpow10(k);
		p = i*primes->ps;
		q = 0;
		for(j=1; j<primes->ps; j++){
			if(j==2 || j==i)
				continue;

			m = primes->pl[j];
			n = m*l + k;
			if(prime_check(primes,n)){
				prop[p+j] = true;
			}else{
				prop[p+j] = false;
			}
		}
	}

	for(i=1; i<primes->ps; i++){
		p = i*primes->ps;
		q = i*primes->ps;
		for(j=i+1; j<primes->ps; j++){
			q += primes->ps;
			prop[p+j] = prop[p+j] && prop[q+i];
			prop[q+i] = prop[p+j];
		}
	}
}

void main(){
	int i,j,k;

	init();
	printf("done\n");
	calc();
	printf("done\n");

	k = 1000000;
	for(i=1; i<primes->ps; i++){
		if(i==2)
			continue;
		j = search(1,i,0,0,0,0);
		if(j){
			printf("%d !\n",j);
			if(j<k){
				printf("!!\n");
				k=j;
			}
		}
	}
}

