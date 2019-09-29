#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>


#define BUFFER_SIZE 26
char Buf[BUFFER_SIZE];
char *pIn, *pOut, *pEnd;
int full;


sem_t pmutex, cmutex;


void initialise(void)
{
	pIn = pOut = Buf;
	pEnd = pIn + BUFFER_SIZE;
	full = 0;
}
void *producer (void *arg)
{
  char *ch;

   ch = (char *)arg;

   while(1){
	   if(pIn == pOut && full)
	   {
		   printf("Buffer is full \n");
		   sleep(1);
	   }
	   sem_wait(&pmutex);
	   printf("P->%c\n",*ch);
	   *pIn++ = *ch;
	   *ch = *ch + 1;
	   if(*ch > 'Z')
		   *ch = 'A';
	   if(pIn > pEnd)
	   {
		   pIn = Buf;
	   }
	   if(pIn == pOut)
	   {
		   full = 1;
	   }
	   sem_post(&pmutex);
	   sleep(1);
   }
}

void *consumer (void *arg)
{
  char *ch;

  ch = (char *)arg;
  while(1){
	  if(pOut == pIn && !full)
	  {
		  printf("Buffer is empty \n");
		  sleep(1);
	  }
	  sem_wait(&cmutex);
	  *ch = *pOut++;
	  printf("C->%c\n",*ch);
	  if(pOut > pEnd)
	  {
		  pOut = Buf;
	  }
	  if(pOut == pIn)
	  {
		  full = 0;
	  }
	  sem_post(&cmutex);
  }
}

int main(int argc, char **argv)
{

   pthread_t tid1, tid2;
   char pch = 'A', cch;

   sem_init(&pmutex,0,1);
   sem_init(&cmutex,0,1);

   initialise();
   pthread_create(&tid1, NULL, producer, (void *)&pch);
   pthread_create(&tid2, NULL, consumer, (void *)&cch);
   pthread_join(tid1, NULL);
   pthread_join(tid2, NULL);

}

