#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

#define CHILD 0

int main()
{
	pid_t childPid;
	int c_status;
	childPid = fork();
//	printf("hello fork %d\n", getpid());
	if (childPid == CHILD) {
		sleep(10);
		printf("child: My pid = %d and ppid = %d\n", getpid(),
		       getppid());
//                while (1) ;
		exit(0);
	} else {
		printf("PARENT :pid = %d and ppid = %d\n", getpid(), getppid());
//		while (1) ;
//		wait(&c_status);
//                sleep(15);
	}


	return 0;
}

/*      
	childpid = fork();
	if (childPid == CHILD) 
		work to be executed in child
	else
		work to be executed in parent
*/





















