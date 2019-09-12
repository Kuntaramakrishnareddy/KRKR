
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS     2

pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int done  = 1;
void *PrintHello(void *threadid)
{
   long tid;
   tid = (long)threadid;
   printf("Thread #%ld!\n", tid);
   pthread_mutex_lock(&lock);
   printf("acquired lock in Thread #%ld!\n", tid);
   if (done == 1) {
   	   done = 2;
	   printf("Waiting on condition variable cond1 tid:%ld\n", tid);
	   pthread_cond_wait(&cond1, &lock);
   }
   else{
	   printf("Signaling condition variable cond1 tid:%ld\n", tid);
	   pthread_cond_signal(&cond1);
   }
   printf("unlock mutex in tid%ld!\n", tid);
   pthread_mutex_unlock(&lock);
   pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
   pthread_t threads[NUM_THREADS];
   pthread_attr_t attr;
   int rc;
   long t;
   void *status;

   /* Initialize and set thread detached attribute */
   pthread_attr_init(&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
   for(t=0; t<NUM_THREADS; t++){
      printf("In main: creating thread %ld\n", t);
      rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
      if (rc){
         printf("ERROR; return code from pthread_create() is %d\n", rc);
         exit(-1);
      }
   }

   /* Free attribute and wait for the other threads */
   pthread_attr_destroy(&attr);
   for(t=0; t<NUM_THREADS; t++){
      rc = pthread_join(threads[t], &status);
      if (rc){
      printf("ERROR; return code from pthread_create() is %d\n", rc);
         exit(-1);
      }
      printf("Main: completed join with thread %ld having a status of %ld\n", t,(long)status);
   }
   printf("Main: program completed. Exiting.\n");

   /* Last thing that main() should do */
   pthread_exit(NULL);
}
