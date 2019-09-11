
/* show how to perform some task periodically
Version : 1.0
Author : Team -C
*/

#include <signal.h>
#include <stdio.h>

void sighand(int signum)
{
	printf("\n %s: \n",__func__);
	printf(" I have to wake up my boss now\n");
	alarm(5);
	sleep(20);
}

main()
{
	signal(SIGALRM, sighand);
	alarm(5);
	while (1) {
		printf("KRKR \n");
		usleep(100000);
	}
}
