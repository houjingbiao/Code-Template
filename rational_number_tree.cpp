#include <stdio.h>
int main(){
   int T;
   scanf("%d", &T);
   int idx = 0;
   while(idx++ < T){
   	int type;
	int n1, n2;
	scanf("%d %d", &type, &n1);
	if(type == 1){
		int mask = 0x40000000;
		while((n1&mask) == 0) mask >>= 1;
		mask >>= 1;		
		int p = 1;
		int q = 1;
		while(mask != 0){
			if((n1 & mask) == 0) q = p+q;
			else q = p+q;
			mask >>= 1;
		}
		printf("case %d: %d %d\n", idx, p, q);
	}
  	else{
		scanf("%d", &n2);
		int number = 0;
		int mask = 1;
		while(n1 != 1 || n2 != 1){
			if(n1 < n2){
				number = number | mask;
				n2 = n2 - n1;
			}
			else n1 = n1 - n2;
			mask <<= 1;
		}
		number |= mask;
		printf("case %d: %d\n", idx, number);
	} 
   }
   return 0;
}
