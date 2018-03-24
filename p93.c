// p93.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define N 1536

bool answer[N];

struct frac{
	int n;
	int d;
};

int perm4[24][4] = {
	{0,1,2,3}, {0,1,3,2}, {0,2,1,3}, {0,2,3,1}, {0,3,1,2}, {0,3,2,1},
	{1,0,2,3}, {1,0,3,2}, {1,2,0,3}, {1,2,3,0}, {1,3,0,2}, {1,3,2,0},
	{2,0,1,3}, {2,0,3,1}, {2,1,0,3}, {2,1,3,0}, {2,3,0,1}, {2,3,1,0},
	{3,0,1,2}, {3,0,2,1}, {3,1,0,2}, {3,1,2,0}, {3,2,0,1}, {3,2,1,0}
};

struct frac *int2frac(int a){
	struct frac *f = malloc(sizeof(struct frac));
	f->n = a;
	f->d = 1;
	return f;
}

bool reduceFrac(struct frac *f){
	if(f->d == 0)
		return false;

	if((f->n)%(f->d) == 0){
		f->n = (f->n) / (f->d);
		f->d = 1;
	}
	return true;
}

bool isWhole(struct frac *f){
	return f->d == 1;
}

bool addf(struct frac *a, struct frac *b, struct frac *c){
	c->n = (a->n)*(b->d) + (a->d)*(b->n);
	c->d = (a->d)*(b->d);
	return reduceFrac(c);
}

bool subf(struct frac *a, struct frac *b, struct frac *c){
	c->n = (a->n)*(b->d) - (a->d)*(b->n);
	c->d = (a->d)*(b->d);
	return reduceFrac(c);
}

bool mulf(struct frac *a, struct frac *b, struct frac *c){
	c->n = (a->n)*(b->n);
	c->d = (a->d)*(b->d);
	return reduceFrac(c);
}

bool divf(struct frac *a, struct frac *b, struct frac *c){
	c->n = (a->n)*(b->d);
	c->d = (a->d)*(b->n);
	return reduceFrac(c);
}

bool calc(struct frac *a, struct frac *b, struct frac *c, int op){
	switch(op){
		case 0: return addf(a,b,c);
		case 1: return subf(a,b,c);
		case 2: return mulf(a,b,c);
		case 3: return divf(a,b,c);
		default: return false;
	}
}

void printfunc(int i){
	switch(i){
		case 0: printf("+ "); break;
		case 1: printf("- "); break;
		case 2: printf("* "); break;
		case 3: printf("/ "); break;
		default: break;
	}
}

void eval43(int *num4){
	int i,j,k;

	struct frac *f[4];
	for(i=0; i<4; i++){
		f[i] = int2frac(num4[i]);
	}

	struct frac *g[3];
	for(i=0; i<3; i++){
		g[i] = int2frac(1);
	}

	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			// 0 1 2 3 _ _ _
			for(k=0; k<4; k++){
				if(!calc(f[2],f[3],g[2],k))
					continue;
				if(!calc(f[1],g[2],g[1],j))
					continue;
				if(!calc(f[0],g[1],g[0],i))
					continue;
				if(isWhole(g[0])){
					int l = g[0]->n;
					if(l>=N || l<=0)
						continue;
					if(answer[l])
						continue;
					answer[l] = true;
					printf("%d %d %d %d ",num4[0],num4[1],num4[2],num4[3]);
					printfunc(k);
					printfunc(j);
					printfunc(i);
					printf("= %d\n",l);
				}
			}
			// 0 1 2 _ 3 _ _
			for(k=0; k<4; k++){
				if(!calc(f[1],f[2],g[2],k))
					continue;
				if(!calc(g[2],f[3],g[1],j))
					continue;
				if(!calc(f[0],g[1],g[0],i))
					continue;
				if(isWhole(g[0])){
					int l = g[0]->n;
					if(l>=N || l<=0)
						continue;
					if(answer[l])
						continue;
					answer[l] = true;
					printf("%d %d %d ",num4[0],num4[1],num4[2]);
					printfunc(k);
					printf("%d ",num4[3]);
					printfunc(j);
					printfunc(i);
					printf("= %d\n",l);
				}
			}
			// 0 1 2 _ _ 3 _
			for(k=0; k<4; k++){
				if(!calc(f[1],f[2],g[2],k))
					continue;
				if(!calc(f[0],g[2],g[1],j))
					continue;
				if(!calc(g[1],f[3],g[0],i))
					continue;
				if(isWhole(g[0])){
					int l = g[0]->n;
					if(l>=N || l<=0)
						continue;
					if(answer[l])
						continue;
					answer[l] = true;
					printf("%d %d %d ",num4[0],num4[1],num4[2]);
					printfunc(k);
					printfunc(j);
					printf("%d ",num4[3]);
					printfunc(i);
					printf("= %d\n",l);
				}
			}
			// 0 1 _ 2 3 _ _
			for(k=0; k<4; k++){
				if(!calc(f[0],f[1],g[2],k))
					continue;
				if(!calc(f[2],f[3],g[1],j))
					continue;
				if(!calc(g[2],g[1],g[0],i))
					continue;
				if(isWhole(g[0])){
					int l = g[0]->n;
					if(l>=N || l<=0)
						continue;
					if(answer[l])
						continue;
					answer[l] = true;
					printf("%d %d ",num4[0],num4[1]);
					printfunc(k);
					printf("%d %d ",num4[2],num4[3]);
					printfunc(j);
					printfunc(i);
					printf("= %d\n",l);
				}
			}
			// 0 1 _ 2 _ 3 _
			for(k=0; k<4; k++){
				if(!calc(f[0],f[1],g[2],k))
					continue;
				if(!calc(g[2],f[2],g[1],j))
					continue;
				if(!calc(g[1],f[3],g[0],i))
					continue;
				if(isWhole(g[0])){
					int l = g[0]->n;
					if(l>=N || l<=0)
						continue;
					if(answer[l])
						continue;
					answer[l] = true;
					printf("%d %d ",num4[0],num4[1]);
					printfunc(k);
					printf("%d ",num4[2]);
					printfunc(j);
					printf("%d ",num4[3]);
					printfunc(i);
					printf("= %d\n",l);
				}
			}
		}
	}
}

void setPerm(int *sour, int *dest, int orde){
	int i;
	for(i=0; i<4; i++){
		dest[i] = sour[perm4[orde][i]];
	}
}

void evalPerm(int *num4){
	int nums[4];
	int i;
	for(i=0; i<24; i++){
		setPerm(num4,nums,i);
		eval43(nums);
	}
}

int countAnswer(){
	int i;
	for(i=1; i<N; i++){
		if(!answer[i])
			break;
	}
	printf("continuous from 1 to %d\n",i-1);
	return i-1;
}

void clearAnswer(){
	int i;
	for(i=0; i<N; i++)
		answer[i] = false;
}

void main(){
	int nums[4];
	int best[4];
	int i,j,k,l;
	int c,d;
	c = 0;
	for(i=1; i<10; i++){
		for(j=i+1; j<10; j++){
			for(k=j+1; k<10; k++){
				for(l=k+1; l<10; l++){
					printf("*** %d %d %d %d ***\n",i,j,k,l);
					clearAnswer();
					nums[0] = i;
					nums[1] = j;
					nums[2] = k;
					nums[3] = l;
					evalPerm(nums);
					d = countAnswer();
					if(c<d){
						c = d;
						best[0] = nums[0];
						best[1] = nums[1];
						best[2] = nums[2];
						best[3] = nums[3];
					}
					printf("\n");
				}
			}
		}
	}
	
	printf("%d, %d%d%d%d\n",c,best[0],best[1],best[2],best[3]);
}