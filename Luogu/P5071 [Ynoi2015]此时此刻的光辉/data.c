#include <stdio.h>
i;
main(){
	freopen("in.in","w",stdout);
	puts("100000 1");
	for (i=0;i<100000;i++){
		printf("998244353%c"," \n"[i==99999]);
	}
	puts("1 100000");
}