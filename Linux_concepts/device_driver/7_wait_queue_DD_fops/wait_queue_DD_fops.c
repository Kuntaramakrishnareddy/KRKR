
#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/slab.h>
#include<linux/uaccess.h>
#include<linux/ioctl.h>
#include<linux/wait.h>
#include<linux/kthread.h>


#define WR_VALUE _IOW('a','a',int32_t*)
#define RD_VALUE _IOR('a','b',int32_t*)

int32_t value = 0;
dev_t dev;
static struct class *dev_class;
static struct cdev rk_cdev;

static int32_t read_count =0;
static struct task_struct *wait_thread;
wait_queue_head_t wait_queue_rk;
int wait_queue_flag = 0;

static int __init rk_init(void);
static void __exit rk_exit(void);
static int rk_open(struct inode *inode, struct file *file);
static int rk_release(struct inode *inode, struct file *file);
static ssize_t rk_read(struct file *file, char __user *buf, size_t len, loff_t *off);
static ssize_t rk_write(struct file *file, const char *buf, size_t len, loff_t *off);
static long rk_ioctl(struct file *file, unsigned int cmd, unsigned long arg);

static struct file_operations fops=
{
   .open = rk_open,
   .release =rk_release,
   .read = rk_read,
   .write = rk_write,
   .unlocked_ioctl = rk_ioctl,
};

static int wait_function(void *unused)
{
	while(1)
	{
		printk(KERN_INFO "Wating for Event...\n");
		wait_event_interruptible(wait_queue_rk, wait_queue_flag !=0);
		if (wait_queue_flag == 2)
		{
			printk(KERN_INFO"Event came from Exit function\n");
			return 0;
		}
		printk(KERN_INFO"Event came from Read function-%d\n", ++read_count);
		wait_queue_flag = 0;

	}
	return 0;
}


static int rk_open(struct inode *inode, struct file *file)
{
  printk(KERN_INFO "%s\n",__LINE__);
  return 0;
}

static int rk_release(struct inode *inode, struct file *file)
{
  printk(KERN_INFO "%s\n",__LINE__);
  return 0;
}

static ssize_t rk_read(struct file *file, char __user *buf, size_t len, loff_t *off)
{
  printk(KERN_INFO "%s\n",__LINE__);
  wait_queue_flag = 1;
  wake_up_interruptible(&wait_queue_rk);
  return 0;
}

static ssize_t rk_write(struct file *file, const char *buf, size_t len, loff_t *off)
{
  printk(KERN_INFO "%s\n",__LINE__);
  return 0;
}

static long rk_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    switch(cmd){
	    case WR_VALUE:
	    	    copy_from_user(&value,(int32_t*) arg, sizeof(value));
	    	    printk(KERN_INFO "value %d\n", value);
	    	    break;
	    case RD_VALUE:
	    	    copy_to_user((int32_t*)arg, &value, sizeof(value));
	    	    break;
    }
    return 0;
}

int __init rk_init(void)
{

    /*Allocate Major number*/
   if((alloc_chrdev_region(&dev, 0, 1, "KRKReddy")) < 0){
	   printk(KERN_ERR "Cannot allocate major number\n" );
	   return -1;
   }

   printk(KERN_INFO "Major num = %d Minor num = %d\n", MAJOR(dev), MINOR(dev));

    /*Create character device structure*/
   cdev_init(&rk_cdev, &fops);

    /*Adding character device to the system*/
   if((cdev_add(&rk_cdev, dev, 1)) < 0){
	   printk(KERN_INFO "Cannot add the device to the system\n");
	   goto r_class;
   }

   /*creating struct class*/
   if((dev_class = class_create(THIS_MODULE, "KRKReddy")) == NULL){
	   printk(KERN_INFO "Cannot create struct class\n");
	   goto r_class;
   }

  if((device_create(dev_class, NULL, dev, NULL, "KRKReddy")) == NULL){
	   printk(KERN_INFO "Cannot create device\n");
	   goto r_device;
  }

  init_waitqueue_head(&wait_queue_rk);

  wait_thread = kthread_create(wait_function, NULL, "WaitThread");
  if(wait_thread){
  	  printk("Thread created successfully\n");
  	  wake_up_process(wait_thread);
  }
  else
  	  printk("Thread creation failed\n");

  printk(KERN_INFO "Device driver inserted successfully...!!\n");
  return 0;

r_device:
  class_destroy(dev_class);
r_class:
  unregister_chrdev_region(dev, 1);
  return -1;
}

void __exit rk_exit(void)
{
  wait_queue_flag = 2;
  device_destroy(dev_class, dev);
  class_destroy(dev_class);
  cdev_del(&rk_cdev);
  unregister_chrdev_region(dev, 1);
  printk(KERN_INFO "Device driver removed successfully...!!\n");
  wait_queue_flag = 1;
}

module_init(rk_init);
module_exit(rk_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("KRKReddy");
MODULE_DESCRIPTION("Device driver with basic file operations sudo code");
MODULE_VERSION("1.5");
