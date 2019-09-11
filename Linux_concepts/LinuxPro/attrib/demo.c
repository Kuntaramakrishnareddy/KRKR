#include<stdio.h>

struct A
{
	int a;
	double d;
	char c;
} __attribute__((packed))obj;

struct B
{
	int r; //4bytes
	double s; //8bytes
	char t;  //1byte
} obj2;
//due to padding 8 + 8 + 8 = 24
int main()
{
	printf("\n %d %d\n",sizeof(obj), sizeof(obj2));
	return 0;
}
