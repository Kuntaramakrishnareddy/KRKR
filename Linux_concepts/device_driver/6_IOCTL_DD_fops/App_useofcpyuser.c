#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<sys/ioctl.h>

#define WR_VALUE _IOW('a','a',int32_t*)
#define RD_VALUE _IOR('a','b',int32_t*)

int main()
{
        int fd, i;
        int32_t value, number, *ptr;
        printf("\nOpening Driver\n");
        fd = open("/dev/KRKReddy", O_RDWR);
        if(fd < 0) {
                printf("Cannot open device file...\n");
                return 0;
        }

       // printf("Enter the Value to send\n");
       // scanf("%d",&number);
	getchar();
        ptr = (int32_t *)malloc(1024*sizeof(int32_t));
        memset(ptr, 0xAA, 1024*sizeof(int32_t));
        printf("Writing Value to Driver %x\n", ptr);
        ioctl(fd, WR_VALUE, ptr);

	getchar();
        printf("Reading Value from Driver\n");
        ioctl(fd, RD_VALUE, ptr);
        for(i = 0; i < 1024; i++)
	{
           printf("%x ", *ptr++);
	}

        printf("Closing Driver\n");
        close(fd);
}
