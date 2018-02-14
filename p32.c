// p32.c
// https://projecteuler.net/problem=32

#include <stdio.h>
#include <stdbool.h>

bool isPandigital(int n){
	bool test[10];
	for(int i=0; i<10; i++){
		test[i] = true;
	}
	int m = n;
	for(int i=0; i<9; i++){
		if(test[m%10] && (m%10)!=0)
			test[m%10] = false;
		else
			return false;
		m/=10;
	}
	return true;
}

void main(){
	int a,b,c,n;
	for(a=2; a<10; a++){
		for(b=1000; b<10000; b++){
			c = a*b;
			if(c>1000 && c<10000){
				n = a + b*10 + c*100000;
				if(isPandigital(n)){
					printf("a:%d, b:%d, c:%d\n",a,b,c);
					//printf("%d+",c);
				}
			}
		}
	}

	for(a=10; a<100; a++){
		for(b=100; b<1000; b++){
			c = a*b;
			if(c>1000 && c<10000){
				n = a + b*100 + c*100000;
				if(isPandigital(n)){
					printf("a:%d, b:%d, c:%d\n",a,b,c);
					//printf("%d+",c);
				}
			}
		}
	}
}
