#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define SEM_NAME "/semaphore_example"
#define ITERS 10

int main(void) {
    sem_t *semaphore = sem_open(SEM_NAME, O_RDWR);
    if (semaphore == SEM_FAILED) {
        perror("sem_open(3) failed");
        exit(EXIT_FAILURE);
    }

    for (;;) {
        if (sem_wait(semaphore) < 0) {
            perror("sem_wait(3) failed on child");
            continue;
        }

        printf("PID %ld acquired semaphore\n", (long) getpid());
        getchar();

        if (sem_post(semaphore) < 0) {
            perror("sem_post(3) error on child");
        }
        sleep(1);

    }

    if (sem_close(semaphore) < 0)
        perror("sem_close(3) failed");

    return 0;
}
