nclude<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>

#define MAX 10

sem_t empty;
sem_t full;
sem_t mutex;

int buf[MAX];
int fill;
int use;
int loop;

void put(int value)
{

        sem_wait(&mutex);
        printf("put item %d\n",value);
        buf[fill]= value;
        fill = (fill+1)%MAX;
        sem_post(&mutex);
}
int get(void)
{
        int item;

        sem_wait(&mutex);
        item = buf[use];
        printf("get item %d\n",item);
        use = (use+1)%MAX;
        sem_post(&mutex);

        return item;
}
void *producer(void *argc)
{
        int i,t;
        printf("Producer \n");
        for(i = 0; i < loop; i++)
        {
                sem_wait(&empty);
                t = i + 10;
                put(t);
                sem_post(&full);
                printf("produced item %d\n",t);
        };
        return 0;
}
void *producer1(void *argc)
{
        int i, t;
        printf("Producer1 \n");
        for(i = 0; i < loop; i++)
        {
                sem_wait(&empty);
                t = i + 20;
                put(t);
                sem_post(&full);
                printf("produced item %d\n",t);
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
void *consumer1(void *argc)
{
        int i, item;
        printf("Consumer1 \n");
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
        sem_init(&mutex,0,1);
        pthread_t pid, cid, p1id,c1id;
        pthread_create(&pid, NULL, (void *)producer, NULL);
        pthread_create(&cid, NULL, (void *)consumer, NULL);
        pthread_create(&p1id, NULL, (void *)producer1, NULL);
        pthread_create(&c1id, NULL, (void *)consumer1, NULL);

        pthread_join(pid, NULL);
        pthread_join(cid, NULL);
        pthread_join(p1id, NULL);
        pthread_join(c1id, NULL);
//      sleep(5);
        printf("producer and consumer are created \n");
        printf("Done Parent \n");
        return 0;
}

