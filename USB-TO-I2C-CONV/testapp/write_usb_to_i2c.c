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

int main()
{

int file;
  int adapter_nr;
  char filename[20];
  __u8 reg = 0x01; /* Device register to access */
  __s32 res;
  char buf[100]="";
  int addr = 0x48; /* The I2C address */
  int i=0,j;

  printf("Enter I2C adapther Number\n");
  j=scanf("%d",&adapter_nr);
  printf("Enter the string you want to send through I2C\n");
  j=scanf("%s",buf);
  char buf_ip[100]="";
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
  //buf_ip[0]=reg;
  while(buf[i] != '\0')
  {
	  buf_ip[i]=buf[i];
	  i++;
  } 
  if (write(file, buf_ip,i+1) != i+1) {
    printf("Unable to write file i2c-%d \n",adapter_nr);
	return -1;
  }
    printf("successfully sent message through i2c-%d \n",adapter_nr);

  close(file);

  return 0;
  
  }
