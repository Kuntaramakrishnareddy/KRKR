#include<stdio.h>

#if 1
int main(void){
	char *p = "KRKReddy";
	char q[] = "Ramakrishna";

	printf("%c\n",*++p);
	/*incrementing base address not valid becasue
	 compiler converts array as const pointer*/
	//printf("%c\n",*++q);

	return 0;
}

#endif

