#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>

sem_t s;

void *child(void *argc)
{
        printf("IN side Child \n");
        sem_post(&s);
        return 0;
}

int main(void)
{
        sem_init(&s,0,0);
        pthread_t c;
        pthread_create(&c, NULL, (void *)child, NULL);
        printf("child created \n");
        sem_wait(&s);
        printf("Done Parent \n");
        return 0;
}

