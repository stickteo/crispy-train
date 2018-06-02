// p61.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define N 10000
#define M 999

struct list{
	int val;
	int typ;
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

int search(struct list *l[], int *u, int n){
	bool b;
	int i, j, k;
	int *u2;
	struct list *m;

	b = u[0] && u[1] && u[2] && u[3] && u[4] && u[5];
	if(b){
		//printf("***%d %d %d %d %d %d\n",u[0],u[1],u[2],u[3],u[4],u[5]);
		return 3;
	} else if(u[0] == 0){
		i = 10;
		while(i<100){
			m = l[i]->next;
			while(m && m->typ==0){
				u[0] = m->val;
				if(search(l, u, u[0])==1){
					//printf("success!\n");
					return 100;
				}
				//printf("**%d %d %d %d %d %d\n",u[0],u[1],u[2],u[3],u[4],u[5]);
				u[0] = 0; u[1] = 0; u[2] = 0; u[3] = 0; u[4] = 0; u[5] = 0;
				m = m->next;
			}
			i++;
		}
		printf("fail\n");
	} else {
		//printf("%d %d %d %d %d %d\n",u[0],u[1],u[2],u[3],u[4],u[5]);
		m = l[n%100]->next;
		i = 0;
		while(m){
			if(u[m->typ]==0){
				u2 = malloc(sizeof(int)*6);
				u2[0] = u[0]; u2[1] = u[1]; u2[2] = u[2];
				u2[3] = u[3]; u2[4] = u[4]; u2[5] = u[5];
				u2[m->typ] = m->val;
				i = search(l, u2, u2[m->typ]);
				if(i==3){
					//printf("*%d %d %d %d %d %d\n",u2[0],u2[1],u2[2],u2[3],u2[4],u2[5]);
					if(u2[m->typ]%100 == u2[0]/100){
						//printf("success!\n");
						printf("****%d %d %d %d %d %d\n",u2[0],u2[1],u2[2],u2[3],u2[4],u2[5]);
						printf("%d\n",u2[0]+u2[1]+u2[2]+u2[3]+u2[4]+u2[5]);
						return 1;
					}
					free(u2);
					return 0;
				}
				if(i==1){
					return 1;
				}
				if(i==0){
					//printf("%d %d %d %d %d %d\n",u2[0],u2[1],u2[2],u2[3],u2[4],u2[5]);
					free(u2);
				}
			}
			m = m->next;
		}
		return 0;
	}
}

void main(){
	int i, j, k;
	int c, d, e, f, g, h;
	//int nums[6][100];
	int used[6];

	struct list *frnt[100];


	for(i=0; i<100; i++){
		frnt[i] = malloc(sizeof(struct list));
		frnt[i]->next = NULL;
	}

	for(k=1; k<=6; k++){
		i=1; j=1; c=1;
		while(i<N){
			if(i>M && (i%100 > 9)){
				struct list *new;
				//printf("%d ",i);
				//nums[k-1][c] = i;
				new = malloc(sizeof(struct list));
				new->val = i;
				new->typ = k-1;
				new->next = NULL;
				addElement(frnt[i/100],new);
				//c++;
			}
			j+=k;
			i+=j;
		}
		//nums[k-1][0] = c;
		//printf("%d\n",c);
	}

	for(i=0; i<100; i++){
		struct list *m;
		m = frnt[i];
		m = m->next;
		while(m){
			//printf("%d %d\n",m->val,m->typ);
			m = m->next;
		}
		//printf("\n*****\n");
	}

	for(i=0; i<6; i++){
		used[i] = 0;
	}

	search(frnt,used,0);

}
