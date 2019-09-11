#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>



int8_t write_buf[1024] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int8_t read_buf[1024];

int main(void)
{
	int fd;
	int option = 0;

	fd = open("/dev/KRKReddy", O_RDWR);
	if(fd < 0){
		printf("Cannot open the file\n");
		return 0;
	}

	while(1)
	{
		printf("\nChoose option \n1->Read\n 2->Write\n 3->Exit\n");
		scanf("%d", &option);
		switch(option){
			case 1:
				read(fd,read_buf,1024);
				printf("Data Red: %s", read_buf);
				break;

			case 2:
				printf("Enter string");
//				scanf("%[^\t\n]s",write_buf);
//				ch = getchar();
//`				collect_str();
//				gets(write_buf);
				write(fd, write_buf, (strlen(write_buf) + 1));
				break;
			case 3:
				close(fd);
				return 0;
			default:
				printf("Invalid option\n");
				break;
		}
	}
	close(fd);
}



