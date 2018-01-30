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
        int fd;
        int value, number;
               
        fd = open("/dev/adc_device", O_RDWR);
        if(fd < 0) {
                printf("Cannot open device file...\n");
                return 0;
        }
 
        printf("Enter Channel Number\n");
        scanf("%d",&number);
        ioctl(fd, WR_VALUE, (int*) &number); 
 
        printf("**********ADC Output***********\n");
        printf("Channel Number: %d\n",number);
        ioctl(fd, RD_VALUE, (int*) &value);
	if(value==0)
        printf("Input Valid Channel Number \n");
        printf("Output Voltage: %d\n",value);
 
        close(fd);
}

