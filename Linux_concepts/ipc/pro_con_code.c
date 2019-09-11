#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

int BUF[5];

sem_t mutex, full;
sem_t empty;



void *producer (void *arg)
{
  int i;
   printf("%s\n", __func__);
   for(i=0; i<5; i++){
   	   sleep(1);
   sem_wait(&empty);
   sem_wait(&mutex);
   printf("%d\n", __LINE__);
   BUF[i]=i*2;
   sem_post(&mutex);
   sem_post(&full);
   }
}

void *consumer (void *arg)
{
  int i;
   printf("%s\n", __func__);
   for(i=0; i<5; i++){
   sem_wait(&full);
   sem_wait(&mutex);
   printf("%d ", BUF[i]);
   sem_post(&mutex);
   sem_post(&empty);
   }
}

int main(int argc, char **argv)
{

   pthread_t tid1, tid2;

   sem_init(&mutex,0,1);
   sem_init(&empty,0,5);
   sem_init(&full,0,0);

   pthread_create(&tid1,NULL,producer,NULL);
   pthread_create(&tid1,NULL,consumer,NULL);

   printf("%s\n", __func__);
   pthread_join(tid1, NULL);
   pthread_join(tid2, NULL);

}

