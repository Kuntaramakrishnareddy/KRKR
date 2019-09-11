#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SEM_NAME "/semaphore_example"
#define SEM_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)
#define INITIAL_VALUE 1

#define CHILD_PROGRAM "./bbb"

int main(void) {

    if (sem_unlink(SEM_NAME) < 0)
        perror("sem_unlink(3) failed");

    /* We initialize the semaphore counter to 1 (INITIAL_VALUE) */
    sem_t *semaphore = sem_open(SEM_NAME, O_CREAT | O_EXCL, SEM_PERMS, INITIAL_VALUE);

    if (semaphore == SEM_FAILED) {
        perror("sem_open(3) error");
        exit(EXIT_FAILURE);
    }


    while(1){

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

    /* Close the semaphore as we won't be using it in the parent process */
    if (sem_close(semaphore) < 0) {
        perror("sem_close(3) failed");
        /* We ignore possible sem_unlink(3) errors here */
        sem_unlink(SEM_NAME);
        exit(EXIT_FAILURE);
    }

    if (sem_unlink(SEM_NAME) < 0)
        perror("sem_unlink(3) failed");

    return 0;
}
