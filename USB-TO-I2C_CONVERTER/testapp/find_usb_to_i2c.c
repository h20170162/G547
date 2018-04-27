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
  unsigned char ad_cnt;

  printf("Enter I2C adapther Number\n");
  j=scanf("%d",&adapter_nr);
  char buf_ip[100]="";
  snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);
  file = open(filename, O_RDWR);
  if (file < 0) {
    printf("Unable to open I2C adapther %s \n",filename);
    return -1;
  }
  
  printf("   00  01  02  03  04  05  06  07  08  09  0a  0b  0c  0d  0e  0f"); 

  for(ad_cnt=0;ad_cnt<128;ad_cnt++)
  {
  if (ioctl(file, I2C_SLAVE, ad_cnt) < 0) {
    printf("Failed in IOCTL \n");
    return -1;
  }
  while(buf[i] != '\0')
  {
	  buf_ip[i]=buf[i];
	  i++;
  }
	
  if ((ad_cnt & 0x0f) == 0) {
        printf("\n%02x:", ad_cnt);
  }

  if (read(file, buf_ip,1) != 1)
  	printf("--  ");
  else
        printf("%02x  ",ad_cnt);
  }
  printf("\n");
  close(file);

  return 0;
  
  }
