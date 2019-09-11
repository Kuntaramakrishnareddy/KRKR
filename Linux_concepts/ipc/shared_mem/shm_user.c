#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main()
{
    /* the size (in bytes) of shared memory object */
    const int SIZE = 4096;

    /* name of the shared memory object */
    const char* name = "OS";

    /* shared memory file descriptor */
    int shm_fd;

    /* pointer to shared memory object */
    int* ptr;

    /* open the shared memory object */
    shm_fd = shm_open(name, O_RDWR, 0666);

    /* memory map the shared memory object */
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    /* read from the shared memory object */

        *ptr = 0x123456;
        getchar();
        *ptr = 0xaabbccdd;
        getchar();
        *ptr = 0x66778899;
        getchar();
        *ptr = 0x98765432;

	printf("\n unlinkkkkkk");
	getchar();



    /* remove the shared memory object */
    shm_unlink(name);
    return 0;
}
