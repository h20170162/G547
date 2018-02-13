#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/ioctl.h>

int main(void)
{
	int channel;
	char channel_num=' ';
	char delay[20];
	char volt_val[20];
	int fd=0;
	char dfilename[]="/dev/timer0";


	// descriptor file open
	fd=open(dfilename, O_RDWR, S_IREAD|S_IWRITE);
	if(fd<0)
	{
		printf("Cannot open device file. Aborting !!\n");
		exit(-1);
	}

	// char driver write
	printf("Enter sleep time:");
	scanf("%d",&channel);
	sprintf(delay,"%d",channel);
	write(fd, delay, sizeof(delay));

	// reading from char driver
	
	read(fd, &volt_val, sizeof(volt_val));
	printf("Timer Value:%s\n",volt_val);

	// file descriptor closing
	close(fd);
	return 0;
}
