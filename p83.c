// p83.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define N 80

int mat[N][N];
int cst[N][N];
bool rch[N][N];

struct cand {
	int m;
	int n;
	struct cand *prev;
	struct cand *next;
};

/*
int mat[N][N] = {
	{131,673,234,103, 18},
	{201, 96,342,965,150},
	{630,803,746,422,111},
	{537,699,497,121,956},
	{805,732,524, 37,331}
};
*/

void parse(FILE *f){
	int c, n, i;
	n = 0; i = 0;
	do {
		c = fgetc(f);
		if(c==',' || c=='\n'){
			mat[i/N][i%N] = n;
			n = 0;
			i++;
			continue;
		}
		n = n*10 + c - '0';
	} while(c != EOF);
}

void removeCand(struct cand *c){
	c->prev->next = c->next;
	c->next->prev = c->prev;
	free(c);
}

void insertAfter(struct cand *a, struct cand *new){
	new->next = a->next;
	new->prev = a;
	a->next->prev = new;
	a->next = new;
}

struct cand *getNext(struct cand *head, struct cand *tail){
	int min;
	struct cand *p, *q;
	min = INT_MAX;
	p = head->next;
	while(p != tail){
		if(cst[p->m][p->n] < min && !rch[p->m][p->n]){
			min = cst[p->m][p->n];
			q = p;
			printf("%d %d %d, ",p->m,p->n,cst[p->m][p->n]);
		}
		p = p->next;
	}
	printf("\n");
	return q;
}

void calcCost(){
	int i, j, k, c;
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			cst[i][j] = INT_MAX;
			rch[i][j] = false;
		}
	}
	struct cand *head = malloc(sizeof(struct cand));
	struct cand *tail = malloc(sizeof(struct cand));
	struct cand *curr = malloc(sizeof(struct cand));
	head->prev = NULL;
	head->next = curr;
	tail->prev = curr;
	tail->next = NULL;
	curr->m = 0;
	curr->n = 0;
	curr->prev = head;
	curr->next = tail;

	cst[0][0] = 0;
	i = 0; j = 0;
	while(!(i == N-1 && j == N-1)){
		c = cst[i][j] + mat[i][j];
		//up
		if(i>0 && !rch[i-1][j] && c<cst[i-1][j]){
			struct cand *p = malloc(sizeof(struct cand));
			p->m = i-1;
			p->n = j;
			insertAfter(head,p);
			cst[i-1][j] = c;
		}
		//down
		if(i<N-1 && !rch[i+1][j] && c<cst[i+1][j]){
			struct cand *p = malloc(sizeof(struct cand));
			p->m = i+1;
			p->n = j;
			insertAfter(head,p);
			cst[i+1][j] = c;
		}
		//left
		if(j>0 && !rch[i][j-1] && c<cst[i][j-1]){
			struct cand *p = malloc(sizeof(struct cand));
			p->m = i;
			p->n = j-1;
			insertAfter(head,p);
			cst[i][j-1] = c;
		}
		//right
		if(j<N-1 && !rch[i][j+1] && c<cst[i][j+1]){
			struct cand *p = malloc(sizeof(struct cand));
			p->m = i;
			p->n = j+1;
			insertAfter(head,p);
			cst[i][j+1] = c;
		}
		rch[i][j] = true;
		removeCand(curr);
		curr = getNext(head,tail);
		i = curr->m;
		j = curr->n;
		//printf(".");	
	}
	printf("%d\n",cst[N-1][N-1]+mat[N-1][N-1]);
}

void main(){
	FILE *f = fopen("p083_matrix.txt","r");
	parse(f);
	fclose(f);
	calcCost();
}
