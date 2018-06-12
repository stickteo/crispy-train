// p94.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define N 1000000000
#define M 22360 // sqrt(N/2)

int main(){
	int a,b,c,m,n,p;
	long ans;
	int mn[2], m2[3], n2[3];

	ans=0;
	m2[0]=4; m2[1]=5; m2[2]=2;
	for(m=2; m<M; m++){
		n2[0]=1; n2[1]=3; n2[2]=2;
		mn[0]=2*m; mn[1]=2*m;

		for(n=1; n<m; n++){
			a = m2[0]-n2[0];
			b = mn[0];
			c = m2[0]+n2[0];

			n2[0]+=n2[1]; n2[1]+=n2[2];
			mn[0]+=mn[1];

			// odd check
			if(c%2==0){ continue; }

			// triangle (c,c,2a)
			// perimeter check and length check
			p=2*(a+c);
			if(p>N){ break; }

			if((c-2*a<=1) && (c-2*a>=-1)){
				printf("a (%d,%d,%d)\n",c,2*a,p);
				ans+=p;
			}

			// triangle (c,c,2b)
			p=2*(b+c);
			if(p>N){ break; }

			if((c-2*b<=1) && (c-2*b>=-1)){
				printf("b (%d,%d,%d)\n",c,2*b,p);
				ans+=p;				
			}
		}

		m2[0]+=m2[1]; m2[1]+=m2[2];
	}
	printf("%ld\n",ans);
}
