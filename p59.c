// p59.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

int count(char *s, char a){
	char *t;
	int b;
	t = s;
	b = 0;
	while(*t){
		if(*t == a)
			b++;
		t += 1;
	}
	return b;
}

void parse(char *s, char *d){
	char *t, *u;
	t = s; u = d;
	while(*t){
		if(t[0]==',' || t[0]=='\n'){
			t += 1;
		}
		else if(t[1]==',' || t[1]=='\n'){
			*u = t[0]-'0';
			t += 2;
			u += 1;
		}
		else if(t[2]==',' || t[2]=='\n'){
			*u = (t[0]-'0')*10 + t[1]-'0';
			t += 3;
			u += 1;
		}
		else if(t[3]==',' || t[3]=='\n'){
			*u = (t[0]-'0')*100 + (t[1]-'0')*10 + t[2]-'0';
			t += 4;
			u += 1;
		}
	}
}

void xor3(char *s, char *d, char *k, int l){
	int i;
	i=0;
	while(i<l){
		d[i] = s[i] ^ k[0];
		d[i+1] = s[i+1] ^ k[1];
		d[i+2] = s[i+2] ^ k[2];
		i+=3;
	}
}

int cost(char *s, int l){
	int i,j;
	i=0; j=0;
	while(i<l){
		if(s[i]>='a' && s[i]<='z')
			j++;
		if(s[i]>='A' && s[i]<='Z')
			j++;
		i++;
	}
	return j;
}

int sum(char *s, int l){
	int i,j;
	i=0; j=0;
	while(i<l){
		j += (s[i] & 0xFF);
		i++;
	}
	return j;
}

void main(){
	char s[5000];
	char *a, *b, *c;
	char d[4];
	int i, j, k, l, m, n;
	FILE *f = fopen("p059_cipher.txt","r");
	fgets(s,5000,f);
	//printf("%s\n",s);
	l = count(s,',')+1;
	a = malloc((l+1)*sizeof(char));
	b = malloc((l+1)*sizeof(char));
	c = malloc((l+1)*sizeof(char));
	a[l]=0;
	b[l]=0;
	c[l]=0;

	parse(s,a);
	
	m = 0; d[3]=0;
	for(i='a'; i<='z'; i++){
		for(j='a'; j<='z'; j++){
			for(k='a'; k<='z'; k++){
				d[0]=i; d[1]=j; d[2]=k;
				xor3(a,b,d,l);
				n = cost(b,l);
				if(n>m){
					printf("%s\n",b);
					printf("%s\n",d);
					printf("%d\n",sum(b,l));
					m=n;
				}
			}
		}
	}
}
