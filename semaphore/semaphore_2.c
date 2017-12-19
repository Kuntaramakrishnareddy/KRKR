#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>

#define MAX 5

sem_t empty;
sem_t full;

int buf[MAX];
int fill;
int use;
int loop;

void put(int value)
{

        printf("put item \n");
        buf[fill]= value;
        fill = (fill+1)%MAX;
}
int get(void)
{
        int item;

        printf("get item \n");
        item = buf[use];
        use = (use+1)%MAX;

        return item;
}

void *producer(void *argc)
{
        int i;
        printf("Producer \n");
        for(i = 0; i < loop; i++)
        {
                sem_wait(&empty);
                put(i);
                sem_post(&full);
                printf("produced item %d\n",i);
        };
        return 0;
}
void *consumer(void *argc)
{
        int i, item;
        printf("Consumer \n");
        for(i = 0; i < loop; i++)
        {
                sem_wait(&full);
                item = get();
                sem_post(&empty);
                printf("consumed item %d\n",item);
        }
        return 0;
}

int main(char *argc, char *argv[])
{
        loop = atoi(argv[1]);
        sem_init(&empty,0,MAX);
        sem_init(&full,0,0);
        pthread_t pid, cid;
        pthread_create(&pid, NULL, (void *)producer, NULL);
        pthread_create(&cid, NULL, (void *)consumer, NULL);

        pthread_join(pid, NULL);
        pthread_join(cid, NULL);
//      sleep(5);
        printf("producer and consumer are created \n");
        printf("Done Parent \n");
        return 0;
}

