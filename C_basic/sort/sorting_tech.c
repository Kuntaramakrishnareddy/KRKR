#include<stdio.h>
#include<string.h>


int max(int a, int b){
	char n1[20];
	char n2[20];
	int ret = 0;

	sprintf(n1, "%d%d",a,b);
	sprintf(n2, "%d%d",b,a);
	ret = strcmp(n1, n2);

	return ret;
}

void swap(int *a, int *b){
	int temp;
	temp = *a;
	*a= *b;
	*b = temp;
}

void sort_largest_posible_num(int *A, int l, int h){
	int i,j, k;

	for(i=0; i <= h; i++){
	    for(j=0; j <= h-i; j++){
		if(max(A[j], A[j+1]) < 0)
			swap(&A[j], &A[j+1]);

		}
	}
}

int partition(int *A, int l, int h){
	int pivot;
	int i, j;

	pivot = A[h];
	i = l - 1;

	for(j = l; j < h; j++){
		if(pivot >= A[j])
			swap(&A[++i], &A[j]);
	}
	swap(&A[++i], &A[h]);

	return i;

}


void quick_sort(int *A, int l, int h){
	int m;
	if(l < h){
		m = partition(A, l, h);
		quick_sort(A, l, m - 1);
		quick_sort(A, m + 1, h);
	}
}

void merge(int *A, int l, int m, int h){
	int i, j, k = 0;
	int B[h - l + 1];

	i = l;
	j = m + 1;
	while((i <= m) && (j <= h)){

		if(A[i] >= A[j])
			B[k++] = A[j++];
		else
			B[k++] = A[i++];
	}
	while(i <= m)
		B[k++] = A[i++];
	while(j <= h)
		B[k++] = A[j++];

	for(i = l; i <= h; i++)
		A[i] = B[i-l];
}

void merge_sort(int *A, int l, int h){
	int m;

	if(l < h){
		m = (l + h)/2;
		merge_sort(A, l, m);
		merge_sort(A, m+1, h);
		merge(A, l, m, h);
	}
}

int main(void){
	//int A[18]={99,88,77,66,55,44,33,22,11,1,2,3,4,5,6,7,8,9};
	int A[8]={1,2,3,4,1,2,3,4};
	int l, h;

	l = 0;
	h = sizeof(A)/sizeof(A[0]);
	printf("h %d l %d \n",h,l);

	merge_sort(A, l, h-1);
	//quick_sort(A, l, h-1);
	//sort_largest_posible_num(A, l, h-1);
	for(l =0; l < h; l++)
		printf("%d ", A[l]);

	printf("\n");
	return 0;
}
