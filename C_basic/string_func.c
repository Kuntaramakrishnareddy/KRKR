#include<stdio.h>

void* memmove_rk(void *dst, const void *src, size_t n){
	char *dst_t;
	const char *src_t;

	src_t = (const char *)src;
	dst_t = (char *)dst;

	/*check for overlapping cases*/
	if(dst_t > src_t && (src_t + n) > dst_t)
	{
		src_t = src_t + n;
		dst_t = dst_t + n;
		while(n--)
		{
			*dst_t = *src_t;
			--dst_t;
			--src_t;
		}
	}
	else{
		while(n--)
		{
			*dst_t = *src_t;
			++dst_t;
			++src_t;
		}
	}
	return dst;
}
int main(void){
	char S1[50] = "Kunta Ramakrishna Reddy";
        char S2[50] = "Hello world dummy";

        printf("S1=%s S2=%s\n",S1, S2);
        memmove_rk(S2+12, S1, 25);
        printf("S1=%s S2=%s\n",S1, S2);
        memmove_rk(S2, S2+12, 25);
        printf("S1=%s S2=%s\n",S1, S2);
        return 0;
}
