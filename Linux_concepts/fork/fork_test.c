
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int *glob_var;
char status = 0;  
int main(void)
{  
int data=0;
int temp = 0;
   glob_var = &data;
    if (fork() == 0) 
	{	
	while(1)
	{
	  if(status == 0)
	   {
		  status = 1;
		  //do some process with var glob_var
		temp++;
	      (*glob_var) = (*glob_var)+2;
		  printf("Value in parent is %d \n",*glob_var );
			sleep(3);
		  status = 0;
		}
	}
    }
    else 
	{
	 while(1)
	 {
	  if(status == 0)
	     {
		  status=1;
		  //do some process with var glob_var
		temp = temp + 2;
	      (*glob_var)++;
		  printf("Value in child is %d \n",*glob_var );
			sleep(1);
		  status = 0;
		 }
	 }
    }
    return 0;
}
