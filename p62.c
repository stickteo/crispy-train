// p62.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define N 10000

struct list {
	int num;
	long val;
	char cnt[10];
	int dgt;
	struct list *nxt;
};

void addElement(struct list *l, struct list *new){
	struct list *m;
	m = l;
	while(m->nxt){
		m = m->nxt;
	}
	m->nxt = new;
}

void count(long n, char *cnt, int *dgt){
	static char c[20];
	int i;
	sprintf(c,"%ld",n);
	i=0;
	while(c[i]){
		cnt[c[i]-'0']++;
		i++;
	}
	*dgt = i;
}

int cmpcnt(char *a, char *b){
	int i;
	for(i=0; i<10; i++){
		if(a[i]<b[i]){
			return -1;
		}else if(a[i]>b[i]){
			return 1;
		}else{
			continue;
		}
	}
	return 0;
}

void main(){
	int n, m;
	long i, j, k, l;
	long z[5];
	struct list *head;
	struct list *e, *f;
	head = malloc(sizeof(struct list));
	head->nxt = NULL;

	n=     345;
	i=41063625;
	j=  356041;
	k=    2064;
	l=       6;

	while(n<N){
		e = malloc(sizeof(struct list));
		e->num = n;
		e->val = i;
		for(m=0; m<10; m++){
			e->cnt[m] = 0;
		}
		e->dgt = 0;
		count(e->val,e->cnt,&e->dgt);
		addElement(head,e);
	
		//printf(".");
		k+=l;
		j+=k;
		i+=j;
		n++;
	}

	e = head->nxt;
	while(e){
		printf("%ld ",e->val);
		m = 1;
		f = e->nxt;
		while(f){
			if(cmpcnt(f->cnt,e->cnt)==0){
				printf("%ld ",f->val);
				m++;
			}
			if(f->dgt > e->dgt)
				break;
			if(m>=5)
				break;
			f = f->nxt;
		}
		printf("%d\n",m);
		if(m>=5)
			break;
		e = e->nxt;
	}


}

