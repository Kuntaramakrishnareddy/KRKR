# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# define BufferSize 10

void *Producer();
void *Consumer();

int BufferIndex=0;
char *BUFFER;

pthread_cond_t empty=PTHREAD_COND_INITIALIZER;
pthread_cond_t full=PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

int main()
{
    pthread_t ptid,ctid;

    BUFFER=(char *) malloc(sizeof(char) * BufferSize);

    pthread_create(&ptid,NULL,Producer,NULL);
    pthread_create(&ctid,NULL,Consumer,NULL);

    pthread_join(ptid,NULL);
    pthread_join(ctid,NULL);


    return 0;
}

void *Producer()
{
    for(;;)
    {
        pthread_mutex_lock(&mutex);
        if(BufferIndex==BufferSize)
        {
            pthread_cond_wait(&empty, &mutex);
        }
        BUFFER[BufferIndex++]='@';
        printf("Produce : %d \n",BufferIndex);
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&full);
    }

}

void *Consumer()
{
    for(;;)
    {
        pthread_mutex_lock(&mutex);
        if(BufferIndex==-1)
        {
            pthread_cond_wait(&full, &mutex);
        }
        printf("Consume : %d \n",BufferIndex--);
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&empty);
    }
}

