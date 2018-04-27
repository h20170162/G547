#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdint.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<linux/i2c-dev.h>
#include<sys/ioctl.h>
#include<fcntl.h>
#include<stdarg.h>
#include<poll.h>
#include<errno.h>
#include<string.h>
#include<ctype.h>

int main()
{

int file;
  int adapter_nr;
  char filename[20];
  __u8 reg = 0x01; /* Device register to access */
  __s32 res;
  char buf[100]="";
  char buf1[100]="";
  int addr; /* The I2C address */
  int i=0,j;

  printf("Enter I2C adapther Number\n");
  j=scanf("%d",&adapter_nr);
  printf("Enter I2C slave address\n");
  j=scanf("%d",&addr);
  snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);
  file = open(filename, O_RDWR);
  if (file < 0) {
    printf("Unable to open I2C adapther %s \n",filename);
    return -1;
  }
  

  if (ioctl(file, I2C_SLAVE, addr) < 0) {
    printf("Failed in IOCTL \n");
    return -1;
  }
  if (read(file, buf,100) != 100) {
    printf("Unable to read from i2c-%d \n",adapter_nr);
	return -1;
  }
    while(isalpha(buf[i]))
    {
	buf1[i]=buf[i];
	i++;
    }
    printf("successfully received message through i2c-%d \n",adapter_nr);
    printf("Received Message : %s\n",buf1);

  close(file);

  return 0;
  
  }
