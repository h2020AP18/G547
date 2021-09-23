#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/random.h>
#include <linux/init.h>
#include <linux/uaccess.h> 
#include <linux/time.h>
#include <linux/sched.h>
#include <linux/slab.h>

#include "chardev.h"
#define DEVICE_NAME "imu_char"
#define SUCCESS 100


static uint16_t message;
//static uint16_t *message_ptr;
static char alignment;


static dev_t first;//variable for device number
static struct cdev c_dev;//variable for the charecter device structure
static struct class *cls;//variable for the device class




static int my_open(struct inode *i,struct file *f)
{
	printk(KERN_INFO "imu_char : open()\n");
        return 0;
}

static int my_close(struct inode *i,struct file *f)
{
	printk(KERN_INFO "imu_char : close()/n");
	return 0;
}

static ssize_t my_read(struct file *f,char __user *buf, size_t len,loff_t *off)
{
	printk(KERN_INFO "imu_char : read()/n");
	
    // Number of bytes  written to the buffer
   // char *b;
   // int bytes_read = 0;
    //int temp;

    #ifdef DEBUG
	printk(KERN_INFO "device_read(%p,%p,%d)\n", file, buf, length);
    #endif


      //put the data into the buffer

     uint16_t random,i;
    get_random_bytes(&i, sizeof(i));
    random = random%1023;
    printk(KERN_INFO "random number : %d\n", i);
    message = random;
    copy_to_user(buf, &message, sizeof(message));



#ifdef DEBUG
	printk(KERN_INFO "Read %d bytes, %d left\n", bytes_read, length);
#endif
	return 10;

}
	
	
static ssize_t my_write(struct file *f,const char __user *buf, size_t len,loff_t *off)
{
	printk(KERN_INFO "imu_char : write()/n");
	return len;
}


static long device_ioctl(struct file *file, unsigned int ioctl_num,unsigned long ioctl_param)

{
    //int i;
    char *temp;
    char ch;
    
    switch (ioctl_num) {
    	case IOCTL_GYROSCOPE_X_AXIS:        	     
    	     temp = (char *)ioctl_param;
             copy_to_user(temp, &message, sizeof(message));
             get_user(ch, temp);
	  alignment = ch;   //ch is the number sent by userspace
         break;         
    case IOCTL_GYROSCOPE_Y_AXIS:  
          temp = (char *)ioctl_param;
          copy_to_user(temp, &message, sizeof(message));  
          get_user(ch, temp);
	  alignment = ch;   
         break;
    case IOCTL_GYROSCOPE_Z_AXIS:           
         temp = (char *)ioctl_param;
        copy_to_user(temp, &message, sizeof(message));  
          get_user(ch, temp);
	 alignment = ch;   
         break;         
    case IOCTL_ACCELEROMETER_X_AXIS:    
          temp = (char *)ioctl_param;
          get_user(ch, temp);
	  alignment = ch;   
         break;        
    case IOCTL_ACCELEROMETER_Y_AXIS:    
          temp = (char *)ioctl_param;
          get_user(ch, temp);
	  alignment = ch;   
         break;                           
    case IOCTL_ACCELEROMETER_Z_AXIS:    
          temp = (char *)ioctl_param;
          get_user(ch, temp);
	  alignment = ch;   
         break;         
    case IOCTL_MAGNETOMETER_X_AXIS:    
          temp = (char *)ioctl_param;
          get_user(ch, temp);
	  alignment = ch;  
         break;         
    case IOCTL_MAGNETOMETER_Y_AXIS:    
          temp = (char *)ioctl_param;
          get_user(ch, temp);
	  alignment = ch;   
         break;                           
    case IOCTL_MAGNETOMETER_Z_AXIS:    
          temp = (char *)ioctl_param;
          get_user(ch, temp);
	  alignment = ch;   
         break;           
    case IOCTL_BAROMETER_PRESSURE:
          temp = (char *)ioctl_param;
          get_user(ch, temp);
	  alignment = ch;   
	break;

    default :  break;
    }

    return SUCCESS;

}





//file operations

static struct file_operations fops =
{
  .owner		= THIS_MODULE,
  .open		= my_open,
  .release		= my_close,
  .unlocked_ioctl	= device_ioctl,
  .read		= my_read,
  .write		= my_write
};



static int __init imu_char_init(void)
{
	printk(KERN_INFO "Namasthe:imu_char driver registered");
	
	//Step_1 <major,minor>
	if(alloc_chrdev_region(&first, 0, 1, "BITS-PILANI") < 0)
	{
		return -1;
	}
	
	//Step_2 creating device node
	if ((cls = class_create(THIS_MODULE, "chardrv")) == NULL)
	{
		unregister_chrdev_region(first, 1);
		return -1;
	}
	
	if(device_create(cls, NULL,first, NULL, "mydevice")==NULL)
	{
		class_destroy(cls);
		unregister_chrdev_region(first ,1);
		return -1;
	}
	
	//Step_3 link fops and cdev to device node
	
	cdev_init(&c_dev, &fops);
	if(cdev_add(&c_dev,first, 1)== -1)
	{
		device_destroy(cls, first);
		class_destroy(cls);
		unregister_chrdev_region(first, 1);
		return -1;
	}
	return 0;
}

static void __exit imu_char_exit(void)
{
	cdev_del(&c_dev);
	device_destroy(cls,first);
	class_destroy(cls);
	unregister_chrdev_region(first, 1);
	printk(KERN_INFO "Bye: imu_char driver unregistered\n\n");
}

module_init(imu_char_init);
module_exit(imu_char_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SUDHEER");
MODULE_DESCRIPTION("imu_char Driver");
	
	
	
	
	
	







