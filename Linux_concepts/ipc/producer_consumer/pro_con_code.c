#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

int BUF[5];

sem_t mutex, full;
sem_t empty;
int buffer_index = 0;
int k=0;

void *producer (void *arg)
{
  int t;

   t = (int)arg;
   printf("%s\n", __func__);

   while(1){
	   usleep(100000);
	   sem_wait(&empty);
	   sem_wait(&mutex);
	   BUF[buffer_index]= k++;
	   printf("%s data %d tid %d index %d\n",__func__, BUF[buffer_index], t, buffer_index);
	   buffer_index++;
	   buffer_index = buffer_index%5;
	   sem_post(&mutex);
	   sem_post(&full);
   }
}

void *consumer (void *arg)
{
  int t;

   t = (int)arg;
   printf("%s\n", __func__);

   while(1){
	   sem_wait(&full);
	   sem_wait(&mutex);
	   if(buffer_index > 0){
		   buffer_index--;
		   printf("%s data %d tid %d index %d\n",__func__, BUF[buffer_index], t, buffer_index);
	   }
	   sem_post(&mutex);
	   sem_post(&empty);
   }
}

int main(int argc, char **argv)
{

   pthread_t tid1, tid2, tid3;
   int t;

   sem_init(&mutex,0,1);
   sem_init(&empty,0,5);
   sem_init(&full,0,0);

   t = 0;
   pthread_create(&tid1, NULL, producer, (void *)t);
   t = 1;
   pthread_create(&tid2, NULL, consumer, (void *)t);
   t = 2;
   pthread_create(&tid3, NULL, producer, (void *)t);

   printf("%s\n", __func__);
   pthread_join(tid1, NULL);
   pthread_join(tid2, NULL);

}

