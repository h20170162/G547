#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include<linux/slab.h>                 //kmalloc()
#include<linux/uaccess.h>              //copy_to/from_user()
#include <linux/ioctl.h>
 #include <linux/random.h>
 
#define WR_VALUE _IOW('a','a',int32_t*)
#define RD_VALUE _IOR('a','b',int32_t*)
 
int32_t value = 0;
unsigned int voltage; 
dev_t dev = 0;
static struct class *dev_class;
static struct cdev adc_cdev;
 
static int __init adc_driver_init(void);
static void __exit adc_driver_exit(void);
static int adc_open(struct inode *inode, struct file *file);
static int adc_release(struct inode *inode, struct file *file);
static ssize_t adc_read(struct file *filp, char __user *buf, size_t len,loff_t * off);
static ssize_t adc_write(struct file *filp, const char *buf, size_t len, loff_t * off);
static long adc_ioctl(struct file *file, unsigned int cmd, unsigned long arg);
 
static struct file_operations fops =
{
        .owner          = THIS_MODULE,
        .read           = adc_read,
        .write          = adc_write,
        .open           = adc_open,
        .unlocked_ioctl = adc_ioctl,
        .release        = adc_release,
};
 
static int adc_open(struct inode *inode, struct file *file)
{
        printk(KERN_INFO "Device File Opened...!!!\n");
        return 0;
}
 
static int adc_release(struct inode *inode, struct file *file)
{
        printk(KERN_INFO "Device File Closed...!!!\n");
        return 0;
}
 
static ssize_t adc_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
        printk(KERN_INFO "Read Function\n");
        return 0;
}
static ssize_t adc_write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
        printk(KERN_INFO "Write function\n");
        return 0;
}
 
static long adc_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	int voltage;
         switch(cmd) {
                case WR_VALUE:
                        copy_from_user(&value ,(int*) arg, sizeof(value));
                        printk(KERN_INFO "Value = %d\n", value);

	
                        break;
                case RD_VALUE:
			     if(value==0||value==2||value==3||value==4||value==5||value==6||value==7)
			get_random_bytes(&voltage,sizeof(voltage));
			else voltage=0;
			if (voltage<0)
			voltage=-(voltage);
			voltage=voltage%1024;
                        copy_to_user((int*) arg, &voltage, sizeof(voltage));
			printk(KERN_INFO "Voltage = %d\n", voltage);                        
			break;
        }
        return 0;
}
 
 
static int __init adc_driver_init(void)
{
        /*Allocating Major number*/
        if((alloc_chrdev_region(&dev, 0, 1, "adc_Dev")) <0){
                printk(KERN_INFO "Cannot allocate major number\n");
                return -1;
        }
        printk(KERN_INFO "Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));
 
        /*Creating cdev structure*/
        cdev_init(&adc_cdev,&fops);
        adc_cdev.owner = THIS_MODULE;
        adc_cdev.ops = &fops;
 
        /*Adding character device to the system*/
        if((cdev_add(&adc_cdev,dev,1)) < 0){
            printk(KERN_INFO "Cannot add the device to the system\n");
            goto r_class;
        }
 
        /*Creating struct class*/
        if((dev_class = class_create(THIS_MODULE,"adc_class")) == NULL){
            printk(KERN_INFO "Cannot create the struct class\n");
            goto r_class;
        }
 
        /*Creating device*/
        if((device_create(dev_class,NULL,dev,NULL,"adc_device")) == NULL){
            printk(KERN_INFO "Cannot create the Device 1\n");
            goto r_device;
        }
        printk(KERN_INFO "Device Driver Insert...Done!!!\n");
    return 0;
 
r_device:
        class_destroy(dev_class);
r_class:
        unregister_chrdev_region(dev,1);
        return -1;
}
 
void __exit adc_driver_exit(void)
{
        device_destroy(dev_class,dev);
        class_destroy(dev_class);
        cdev_del(&adc_cdev);
        unregister_chrdev_region(dev, 1);
    printk(KERN_INFO "Device Driver Removed\n");
}
 
module_init(adc_driver_init);
module_exit(adc_driver_exit); 
MODULE_LICENSE("GPL");

